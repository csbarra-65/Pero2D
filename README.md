First simulation of a simple 3D structure of gold electrodes and 2D perovkskite

Parameters:
Pero2D Material: Either Br or I flavor; Pero2D layer thickness and width (distance between electrodes)

Gold electrodes: included or not, variable size;

scintillator: included or not, variable thickness;

Kapton supporting foil: included or not, variable thickness;

If run without a macro, uses visualization and the followinf default values:

Pero layer Thickness = 0.1 * mm;
Distance between elctrodes = 2.0 * mm;
flavorBr = false;

Kapton foil exists; 
kapton foilThickness = 0.5 * mm;

gold electrodes exist;
electrodes size is 1 mm;

Scintillator is included ;
scintThickness = 1.0 * mm;

If run without passing any macro, defaults are used and visualization is started.
ExampleMacro.mac shows how to change default behaviour.
Simulation results are saved in root ntuples.
