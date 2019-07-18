==== How to run doubleHiggs limits ===

0. Prepare the analyzedOutPlotter.root files

1. Open MakeLimits.py and edit the necessary lines in the "CONFIGURABLES SECTION", the possible options are:
	- doCOmbination  : do the channels/category combination or not
	- OUTSTRING      : nametag of the output directory
	- intag          : nametag of the input directory (containing analyzedOutPlotter.root)
	- SELECTIONS     : present in the analyzedOutPlotter.root file
	- CHANNELS       : present in the analyzedOutPlotter.root file
	- LAMBDAS        : for the non-resonant case list here the values of kl analyzed
	- LM/MM/HM_MASSES: for the resonant case list here the values of mHH analyzed

2. Run the MakeLimits.py script:
	- Non-resonant case: python MakeLimits.py -r 0
	- Resonant case    : python MakeLimits.py -r 1 -s 0/2 [0:Radion, 2:Graviton]

3. Open MakePlotSimple.py and edit the necessary lines in the "CONFIGURABLES SECTION", the possible options are:
	- channels/channelsName : the channels considered and their LaTeX names
	- folder                : tagname of the input folders containing the limits (must be the same used in MakeLimits.py)
	- masses                : for the resonant and non-resonant case list here the values of kl/mHH analyzed (must be the same used in MakeLimits.py)
	- categories            : analyzed categories  (must be the same used in MakeLimits.py)

4. Run the MakePlotSimple.py script:
	- Resonant case  : python MakePlotSimple.py -x 999 -o [output tagname] -s 0/2 [0:Radion, 2:Graviton]
	- Lambda scan    : python MakePlotSimple.py -x   0 -o [output tagname]
	- Benchmark scan : python MakePlotSimple.py -x   1 -o [output tagname]  <-- Not working for now!!
   Other options can be found in the script


==== To be fixed ====
- add a switch for GGF/VBF production modes
- check if QCD is correctly taken into account
- check bin-by-bin systematic uncertainties (not working for now)


OLD:
==== Note on systematics ===
Log-normal Systematics are defined in config/systematics*cfg and read via systReader.py
Name of the processes in the config file should match those in mainCfg.cfg. If not, add manually the relevant names in ALL the syst*cfg files

Shape systematics are added in chcardMaker.py Look for the line with "AddSyst"
Names should match those in the wrapperHisto.py macro

Bin-by-bin is performed autmatically if chcardMaker is ran with the "-y" option
