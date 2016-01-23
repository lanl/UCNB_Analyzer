// Copyright 2016.  Los Alamos National Security, LLC.
// This file is part of UCNB_Analyzer.
// This program is distributed under the terms of the GNU General Public License, version 2.0.  See LICENSE.md included in top directory of this distribution.

// File: SiCalibrator.hh
// Purpose: Calibrates silicon detectors using known sources
 
#ifndef SI_CALIBRATOR_HH__
#define SI_CALIBRATOR_HH__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "TSystem.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TrapTreeFile.hh"

#define MAXPIX 48
#define MAXADCVAL 16000

using std::cout;
using std::endl;
using std::vector;

class SiCalibrator
{
private:
	vector<int> detector;
	struct SourceLine_t {
		double E;
		double Edet; //after foil/deadlayer
		double branch;
	};
	struct CalibSource_t {
		std::string name;
		int type;
		vector<SourceLine_t> betas;
		vector<SourceLine_t> xrays;
	};
	vector<CalibSource_t> sourcelist;
	int maxtype;
	struct ChData_t {
		vector<TF1*> fits;
		TF1* fpol1;
		TF1* fpol2;
	};
	struct CalibData_t {
		TH2D* hSource;
		vector<ChData_t> sourcedata;
	};
	vector<CalibData_t> CalData;
	struct RunLog_t {
		int filenum;
		int type[2];
	};
	vector<RunLog_t> runlist;
public:
	SiCalibrator();
	~SiCalibrator();
	void DefineSources();
	void DefineDetector(vector<int> newdetector) {detector.swap(newdetector);};
	void DefineRunLog(vector<int> runlist, vector<int> type);
	void DefineRunLog(vector<int> runlist, vector<int> type1, vector<int> type2);
	void BuildHists(TrapTreeFile &trapf);
  
};

#endif // SI_CALIBRATOR_HH__
