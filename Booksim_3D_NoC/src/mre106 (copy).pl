#!/usr/bin/perl
#use strict;
use warnings;
my $startVal = 0.002;
my $endVal = 0.02;
my $incrementVal = 0.002;
my $StartVC=8;

use warnings;

my @traffList = ("uniform","transpose"); #
my $path1 = "./examples/b1";
my $path2= "./examples/b2";
my $path3 = "./examples/b3";
my $path4= "./examples/b21";
my $path5= "./examples/m1";
my $path6= "./examples/m2";
my $path7= "./examples/m3";


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


for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="b1_".$tra.$tempPath;
	print $tempPath;



	my $ps=$tra;

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path1 > $resultPath/$i.txt`;
	`killall booksim`;
	}
}


for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="b2_".$tra.$tempPath;
	print $tempPath;

	my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path2 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}
for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="b3_".$tra.$tempPath;
	print $tempPath;


		my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path3 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}
for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="b21_".$tra.$tempPath;
	print $tempPath;
	my $ps=$p[$k];
	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path4 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}
for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="m1_".$tra.$tempPath;
	print $tempPath;
	my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path5 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}
for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="m2_".$tra.$tempPath;
	print $tempPath;
	my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path6 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}
for (my $a = 0; $a<2; $a=$a+1)
{
	my $d="_";
	my $tra=$traffList[$a];
	$tempPath="m3_".$tra.$tempPath;
	print $tempPath;
	my $ps=$p[$k];

	for(my $i= $startVal; $i<$endVal; $i=$i+$incrementVal)
	{
	my $resultPath = "./result/$tempPath/$ps";
	`mkdir -p $resultPath`;
	`./booksim injection_rate=$i   traffic=$tra $path7 > $resultPath/$i.txt`;
	`killall booksim`;
	}

}


