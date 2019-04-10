#include "SIM_port.h"
#include "SIM_router_model.h"
#include "SIM_link_model.h"
#include <stdio.h>



double 	PARM_Vdd ;//	=      	1.0;
double 	PARM_tr ;//	= 	0.1 ;
double 	PARM_Freq;//	=	1e9;
int   	PARM_in_port;// 	=	5;
int   	PARM_out_port;//	=	5;
int 	PARM_flit_width;//	=       128;
float   bitwidth64x    =       1.0;
int 	PARM_v_class ;//   =	1;   /* # of total message classes */
int	PARM_v_channel	;//=	2;	/* # of virtual channels per virtual message class*/
int 	PARM_in_share_buf ;//=	0;	/* do input virtual channels physically share buffers? */
int 	PARM_out_share_buf;//=	0;	/* do output virtual channels physically share buffers? */
int 	PARM_crossbar_model;//=	MULTREE_CROSSBAR;	/* crossbar model type MATRIX_CROSSBAR, MULTREE_CROSSBAR, or TRISTATE_CROSSBAR (only for Orion3.0)*/ 
int	PARM_crsbar_degree;//=	4;					/* crossbar mux degree */
int	PARM_connect_type;//=	TRISTATE_GATE;		/* crossbar connector type */
int	PARM_trans_type;//=	NP_GATE;
int 	PARM_in_buf;//=1;//			1		/* have input buffer? */
int 	PARM_in_buf_set;//=8;//		//number of buffer slots per VC per port, 0 is automatically converted to 1	
int 	PARM_in_buffer_type;//= SRAM ;//SRAM	/*buffer model type, SRAM or REGISTER*/
int 	PARM_out_buf;//=0	;//		0
int 	PARM_out_buf_set;//=0;//		2
int 	PARM_out_buffer_type;//=SRAM;//  	SRAM		/*buffer model type, SRAM or REGISTER*/
int 	PARM_sw_in_arb_model;//= RR_ARBITER;//		/* input side arbiter model type, MATRIX_ARBITER , RR_ARBITER, QUEUE_ARBITER*/
int	PARM_sw_out_arb_model;//=	RR_ARBITER;//	/* output side arbiter model type, MATRIX_ARBITER */
int 	PARM_vc_allocator_type;//=	TWO_STAGE_ARB;//	/*vc allocator type, ONE_STAGE_ARB, TWO_STAGE_ARB, VC_SELECT*/
int 	PARM_vc_in_arb_model;//= 	RR_ARBITER;//    /*input side arbiter model type for TWO_STAGE_ARB. MATRIX_ARBITER, RR_ARBITER, QUEUE_ARBITER*/
int 	PARM_vc_out_arb_model;// =	RR_ARBITER ;// 	/*output side arbiter model type (for both ONE_STAGE_ARB and TWO_STAGE_ARB). MATRIX_ARBITER, RR_ARBITER, QUEUE_ARBITER */
//link wire parameters
/*
int 	WIRE_LAYER_TYPE =        INTERMEDIATE ;//wire layer type, INTERMEDIATE or GLOBAL
int 	PARM_width_spacing  =    DWIDTH_DSPACE  ; //choices are SWIDTH_SSPACE, SWIDTH_DSPACE, DWIDTH_SSPACE, DWIDTH_DSPACE
int 	PARM_buffering_scheme=   MIN_DELAY ;  	//choices are MIN_DELAY, STAGGERED 
int 	PARM_shielding      =    0;   		//choices are TRUE, FALSE 

//clock power parameters
int 	PARM_pipeline_stages  =  4  ; 	//number of pipeline stages
int 	PARM_H_tree_clock    =   0  ;     //1 means calculate H_tree_clock power, 0 means not calculate H_tree_clock
int	PARM_router_diagonal =   442 ; 	//router diagonal in micro-meter 
*/

int Flexus_Orion_init(const Configuration& config)
{
   //printf("\n------ orion init---------\n");
   PARM_Vdd = 		config.GetFloat( "Vdd" );//
   PARM_tr = 		config.GetFloat( "Orion_tr" );//0.2 ;
   PARM_Freq=		config.GetFloat( "Orion_Freq" );// 1e9;
   
   PARM_in_port=	config.GetInt( "Orion_inport" );//5;
   PARM_out_port=	config.GetInt( "Orion_outport" );//5;
   PARM_flit_width=	config.GetInt( "Orion_bitwidth" );//64;
   if(PARM_flit_width>64)
   {
     bitwidth64x = float(PARM_flit_width) / 64.0;
     PARM_flit_width =64;
   }
     
   PARM_v_class = 	config.GetInt( "Orion_vc_class" );//1;   /* # of total message classes */
   PARM_v_channel =	config.GetInt( "num_vcs" );	/* # of virtual channels per virtual message class*/
   
   //printf("param  fromfile: %g\n", PARM_Vdd);
   //exit(0);
   
   PARM_in_share_buf=	config.GetInt("Orion_IsSharedBuffIn");// 0;	/* do input virtual channels physically share buffers? */
   PARM_out_share_buf=	config.GetInt("Orion_IsSharedBuffOut");//0;	/* do output virtual channels physically share buffers? */
   PARM_crossbar_model=	config.GetInt( "Orion_crossbar_model");//MULTREE_CROSSBAR;	/* crossbar model type MATRIX_CROSSBAR, MULTREE_CROSSBAR, or TRISTATE_CROSSBAR (only for Orion3.0)*/ 
   PARM_crsbar_degree=	config.GetInt("Orion_crsbar_degree");//4;					/* crossbar mux degree */
   PARM_connect_type=	config.GetInt("Orion_Cxbar_Cxpoint");//TRISTATE_GATE;		/* crossbar connector type */
   PARM_trans_type=	config.GetInt("Orion_trans_type");//NP_GATE;				/* crossbar transmission gate type */
   PARM_in_buf=         config.GetInt("Orion_IsInBuff");//1;//			1		/* have input buffer? */
   PARM_in_buf_set=     config.GetInt("vc_buf_size");//8;//		1	
   
   PARM_in_buffer_type= config.GetInt("Orion_buff_type");//SRAM ;//SRAM	/*buffer model type, SRAM or REGISTER*/
   
   
   PARM_out_buf=        config.GetInt("Orion_IsOutBuff");//0	;//		0
   PARM_out_buf_set=    config.GetInt("Orion_out_buf_size");//0;//		2
   PARM_out_buffer_type=        config.GetInt("Orion_buff_type");//SRAM;//  	SRAM		/*buffer model type, SRAM or REGISTER*/
   PARM_sw_in_arb_model=        config.GetInt("Orion_in_arb_model");//RR_ARBITER;//		/* input side arbiter model type, MATRIX_ARBITER , RR_ARBITER, QUEUE_ARBITER*/
   PARM_sw_out_arb_model=	config.GetInt("Orion_out_arb_model");//RR_ARBITER;//	/* output side arbiter model type, MATRIX_ARBITER */
   PARM_vc_allocator_type=	config.GetInt("Orion_allocator_model");//TWO_STAGE_ARB;//	/*vc allocator type, ONE_STAGE_ARB, TWO_STAGE_ARB, VC_SELECT*/
   PARM_vc_in_arb_model= 	config.GetInt("Orion_in_vc_arb_model");//RR_ARBITER;//    /*input side arbiter model type for TWO_STAGE_ARB. MATRIX_ARBITER, RR_ARBITER, QUEUE_ARBITER*/
   PARM_vc_out_arb_model =	config.GetInt("Orion_out_vc_arb_model");//RR_ARBITER ;// 	/*output side arbiter model type (for both ONE_STAGE_ARB and TWO_STAGE_ARB). MATRIX_ARBITER, RR_ARBITER, QUEUE_ARBITER */

   
  
  return 0;
}
