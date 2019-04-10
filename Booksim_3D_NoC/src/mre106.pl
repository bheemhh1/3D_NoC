#!/usr/bin/perl
#use strict;
use warnings;
my $startVal = 0.02;
my $endVal = 0.18;
my $incrementVal = 0.02;
my $StartVC=8;

use warnings;

my @traffList = ("uniform","transpose"); #
my $path1 = "./examples/m2";
my $path2= "./examples/b2";
my $path3 = "./examples/b2";
my $path4= "./examples/b21";
my $path41= "./examples/b22";
my $path5= "./examples/m1";
my $path6= "./examples/m2";
my $path7= "./examples/m3";


my @valueList = ("Overallaverage network latency","Overall average hops");
#my $path = "./examples/bftree1";
chomp(my $tempPath1 = `date +%d_%b_%H-%M`);
	#	my $d="_";
	#	$tempPath="mesh_with_delay_10e5".$tempPath;
	#	print $tempPath;
if(@ARGV)
{
    $path = $ARGV[0];
}




for (my $a = 0; $a<3; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="mipro_M2_".$tra.$tempPath;
	print $tempPath;

	my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path1 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}




