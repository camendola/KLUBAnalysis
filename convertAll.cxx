void convertAll(){
  gROOT->ProcessLine(".L convert.cc");
  for(int ii = 0; ii<92; ii++){
      gROOT->ProcessLine(Form("convert(%d)",ii));
    }
}
