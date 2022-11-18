Analyze : NanAODEgammaReader.C
	g++ NanAODEgammaReader.C NanAODEgammaReader.h `root-config --cflags --glibs` -o Analyze
clean : 
	rm Analyze
