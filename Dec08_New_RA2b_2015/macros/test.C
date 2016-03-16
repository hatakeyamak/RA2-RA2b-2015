test(){

cout << "hello all" << endl;

TH1D * h = new TH1D("h","test",10,0,10);
TCanvas* canvas = new TCanvas("canvas","canvas",10,10,600,800);

h->Fill(5);

h->Draw();

canvas->Print("test.png");

}