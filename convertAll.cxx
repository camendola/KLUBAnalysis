void convertAll(){
  gROOT->ProcessLine(".L convert.cc");
  for(int ii = 90; ii<92; ii++){
      gROOT->ProcessLine(Form("convert(%d)",ii));
    }
}

