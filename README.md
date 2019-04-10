-----------------------------------------------------------------------------------------------------
## BookSim Interconnection Network Simulator
-----------------------------------------------------------------------------------------------------
You can use the [editor on GitHub](https://github.com/bheemhh1/3D_NoC/edit/master/README.md) to maintain and preview the content for your website in Markdown files.

BookSim is a cycle-accurate interconnection network simulator. Originally developed for and introduced with the Principles and Practices of Interconnection Networks book(http://cva.stanford.edu/books/ppin/), its functionality has since been continuously extended. The current major release, BookSim 2.0, supports a wide range of topologies such as mesh, torus and flattened butterfly networks, provides diverse routing algorithms and includes numerous options for customizing the network's router microarchitecture.

If you use BookSim in your research, we would appreciate the following citation in any publications to which it has contributed:

Nan Jiang, Daniel U. Becker, George Michelogiannakis, James Balfour, Brian Towles, John Kim and William J. Dally. A Detailed and Flexible Cycle-Accurate Network-on-Chip Simulator. In Proceedings of the 2013 IEEE International Symposium on Performance Analysis of Systems and Software, 2013.

-----------------------------------------------------------------------------------------------------
## HotSpot 6.0
-----------------------------------------------------------------------------------------------------
HotSpot is a computationally efficient, architecture level thermal modeling
infrastructure developed at the University of Virginia. It makes use of the
duality that exists between the electrical and thermal properties of materials
to model processor temperature. It is written in 'C' and can be easily
interfaced with typical power/performance simulators available in the
community. It can be downloaded from http://lava.cs.virginia.edu/HotSpot
Contact: Runjie Zhang, runjie@virginia.edu

The changes documented in this release are partly sponsored by 
Defense Advanced Research Projects Agency(DARPA), Microsystems Technology Office (MTO),
under contract no. HR0011-13-C-0022.

This release of HotSpot incorporates the following changes/improvements:


1) Calibration and validation 
-----------------------------------------------------------------------------------------------------
- Acknowledgements: Pritish R. Parida at IBM and Pradip Bose at IBM

Please refer to our technical report for more details.


2) New Feature: Fast steady-state solver based on SuperLU.
-----------------------------------------------------------------------------------------------------
To speedup grid-mode's steady-state simulations, we implemented a new, direct solver based on SuperLU. 
SuperLU is an open source library for the direct solution of large, sparse systems of 
linear equations. Documentations, installation instructions and source code can be found here: 
http://crd-legacy.lbl.gov/~xiaoye/SuperLU/

According to our internal tests, this new direct solver could be 10x-100x faster than 
the iterative solver used by previous versions of HotSpot. However, due to its large memory usage,
direct solver will significantly slowdown when the problem size (grid-size, number of layers in a 
3D chip) is large. For this reason, we recommend using direct solver in these two situations:
a. Grid size is relatively small. (e.g. no larger than 256x256 for a 4-layer 3D chip).
   If the host machine's memory is small (<8GB), even smaller grid-size is preferred.
b. detailed_3D mode is enabled.


3) New Feature: Support layers with non-uniform thermal resistivity and heat capacity.
-----------------------------------------------------------------------------------------------------
- By Ayse K. Coskun, Katsutoshi Kawakami, Daniel Rossell, and Samuel Howes at Boston University.
- Contact: acoskun@bu.edu
- Acknowledgements: Tiansheng Zhang and Fulya Kaplan at Boston University; Yasuko Eckert and Wei Huang at AMD; 
  David Atienza, Mohamed M. Sabry, and Yusuf Leblebici at EPFL; and Tajana Rosing at UCSD.

This feature is contributed by Prof. Ayse Coskun's research group in Boston University.
It enables modeling for layers with blocks that have a heterogeneous set of thermal 
resistivity and heat capacity values. All major related code revisions are commented with "BU_3D".

To enable this new feature in simulation, cmd line option 'detailed_3D' should be set to 'on'.
Currently, heterogeneous layers could only be modeled in grid-mode with .lcf file specified.
There is a slight change in the format of the floorplan file (.flp) that allows units in
the floorplan to have different heat capacitance and resistivity (see the example below). 
Note that specific-heat and resistivity are optional. Leaving them blank will force HotSpot 
to use layers' default RC values (specified in .lcf file) for that block. 


-----------------------------------------------------------------------------------------------------
### Extending BookSim2.0 and HotSpot6.0 for Power, Performance and Thermal evaluation of 3D NoC Architectures
( 3D NOC Power, Performance and Thermal analysis)

-----------------------------------------------------------------------------------------------------
3D NoC (BookSim) 
-----------------------------------------------------------------------------------------------------
The major extensions incorporated in BookSim2.0 are: Through Silicon Via power and performance models, 
3D topology construction modules, 3D Mesh topology construction using variable X,Y,Z radix, tailored 
routing modules for 3D NoCs. 

-----------------------------------------------------------------------------------------------------
3D NoC (Hotspot6.0)
-----------------------------------------------------------------------------------------------------
The major extensions incorporated in HotSpot6.0 are: parameterized  2D router floorplan, 3D router floorplan including Through Silicon Vias (TSVs), power and thermal distribution models of 2D and 3D routers

#### for more information check  : > Howt_3D_NoC file

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
