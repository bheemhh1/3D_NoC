# HotSpot Support for 3D NoCs
## Topologies Supported:
- 3D Mesh
- 3D Mesh with router shifted to the center 
- 3D Concentrated Mesh
- 3D Butterfly Fat Tree

## Usage

1. Use any of the .py files to generate the floorplan files(.flp) for any topology. Parameters concerning the number of cores per layer and number of layers can be edited within the script. A corresponding power trace (.ptrace) file will also be generated. \
Note: To view a generated floorplan after running any .py script \
./tofig.pl <floorplan filename>.flp  | fig2dev -L ps | ps2pdf - <output filename>.pdf

2. Edit any one of the layer configuration (NoC_x.lcf) files based on the number of layers generated from the python script as follows:\
Silicon_layer_0.flp \
Thermal_interface_layer_0.flp \
Silicon_layer_1.flp \
Thermal_interface_layer_1.flp \
. \
. \
Thermal_interface_layer_n-1.flp \
Silicon_layer_n.flp \
Thermal_Interface_Material.flp (Heat Sink)

3. To run the Hotspot Simulation  


./hotspot -c hotspot.config -f <any .flp filename>.flp -p <generated ptrace filename>.ptrace -steady_file <min/max/avg/center>.steady -model_type grid -detailed_3D on -grid_layer_file <NoC layer configuration filename>.lcf -grid_map_mode <min/max/avg/center> -grid_steady_file <min/max/avg/center>.grid.steady

 
Note: Ensure min/max/avg/center remains consistent across all filenames inorder to avoid confusion during experimentation. Also since detailed_3D is 'on', the argument passed under -f (floorplan file) does not matter as it will be overriden by the layer configuration file which contains the necessary floorplan files for the simulation.

4. To generate graphs of router temperatures after completing the simulation, run the following in the exact specified order: 
    - python simplify.py
    - python routerplot.py
    - python plotstats.py \
Caution: The output filename within routerplot.py and input filename within plotstats.py should match

5. To Generate thermal heatmaps after completing the simulation, run: \
    ./grid_thermal_map.pl <.flip filename> <min/max/avg/center>.grid.steady > <min/max/avg/center>.svg

## Citation
In case you use this repository for your own research, kindly cite the following articles from SPARK Lab, NITK Surathkal:
1. [Accurate Power and Latency Analysis of a Through-Silicon Via(TSV)](https://ieeexplore.ieee.org/document/8554639)
2. [Thermal Aware Design for Through-Silicon Via (TSV) based 3D Network-on-Chip (NoC) Architectures](https://drive.google.com/file/d/1tZgL_-6pjEv_qYeS4k2Wiie2KGYZFd81/view)

Also cite the following supporting articles:
1. [Differentiating the roles of IR measurement and simulation for power and temperature-aware design](https://ieeexplore.ieee.org/document/4919633)
2. [ORION 2.0: A fast and accurate NoC power and area model for early-stage design space exploration](https://ieeexplore.ieee.org/document/5090700)
3. [SPEC CPU2000: measuring CPU performance in the New Millennium](https://ieeexplore.ieee.org/document/869367)

## Team
1. [Ujjwal Pasupulety](https://www.linkedin.com/in/ujjwalpasupulety/) (Final Year Undergraduate, Dept. of Information Technology, NITK Surathkal)
2. [Bheemappa Halavar](http://cse.nitk.ac.in/researchscholars/bheemappa-h-halavar) (Phd Scholar, Dept. of Computer Science and Engineering, NITK Surathkal)
3. [Basavaraj Talawar](http://bt.nitk.ac.in/index.html) (Assistant Professor, Dept. of Computer Science and Engineering, NITK Surathkal)
