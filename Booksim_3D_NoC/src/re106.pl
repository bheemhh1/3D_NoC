#!/usr/bin/perl
#use strict;
use warnings;
my $startVal = 0.02;
my $endVal = 0.2;
my $incrementVal = 0.02;
my $StartVC=8;

use warnings;
my @vc=("8");
my @p=("5");
my @vcd=("16");
my @traffList = ("uniform","transpose"); #("uniform","transpose","hotspot","bitrev","bitcomp","tornado"); 
my $path = "./examples/bftree3";
my @valueList = ("Overallaverage network latency","Overall average hops");
#my $path = "./examples/bftree1";
chomp(my $tempPath = `date +%d_%b_%H-%M`);
	#	my $d="_";
	#	$tempPath="mesh_with_delay_10e5".$tempPath;
	#	print $tempPath;
if(@ARGV)
{

    $path = $ARGV[0];
}
for (my $a = 0; $a<6; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="bft4La11_".$tra.$tempPath;
	print $tempPath;
for (my $k = 0; $k<1; $k=$k+1)
{
	my $vc2=$vc[$k];	
for (my $j = 0; $j<1; $j=$j+1)
{
	my $vc1=$vcd[$j];
	for (my $k = 0; $k < 1; $k++) 
	{
		my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$vc2$d$vc1$d$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i packet_size=$ps num_vcs=$vc2 vc_buf_size=$vc1 traffic=$tra $path > $resultPath/$vc2$d$vc1$d$i.txt`;
	`killall booksim`;
	}
	}
	}
}
}
