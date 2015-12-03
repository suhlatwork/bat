#ifndef __BCMTFANALYSISFACILITY__H
#define __BCMTFANALYSISFACILITY__H

/*!
 * \class BCMTFAnalysisFacility
 * \brief A class summarizing a set of predefined measurements.
 * \author Daniel Kollar
 * \author Kevin Kr&ouml;ninger
 * \version 1.1
 * \date 06.2012
 * \detail This class defines a set of measurements.
 */

/*
 * Copyright (C) 2007-2015, the BAT core developer team
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 * For documentation see http://mpp.mpg.de/bat
 */

// ---------------------------------------------------------
#include <string>
#include <vector>

#include <TH1D.h>

#include "../../BAT/BCLog.h"

class BCMTF;
class TTree;
class TRandom3;

// ---------------------------------------------------------
class BCMTFAnalysisFacility
{

public:

    /** \name Constructors and destructors */
    /** @{ */

    /**
     * The default constructor.
     * @param mtf The MTF object. */
    BCMTFAnalysisFacility(BCMTF* mtf);

    /**
     * The default destructor. */
    ~BCMTFAnalysisFacility();

    /** @} */
    /** \name Member functions (get) */
    /** @{ */

    /**
     * @return A pointer to the MTF object. */
    BCMTF* GetBCMTF()
    { return fMTF; };

    /** @} */
    /** \name Member functions (set) */
    /** @{ */

    /**
     * Set the pointer to an MTF object.
     * @param mtf The MTF object. */
    void SetBCMTF(BCMTF* mtf)
    { fMTF = mtf; };

    /**
     * Set a flag for using MCMC (true) or not (false).
     * @param flag The flag. */
    void SetFlagMarginalize(bool flag)
    { fFlagMarginalize = flag; };

    /** @} */
    /** \name Member functions (miscellaneous methods) */
    /** @{ */

    // misc

    /**
     * Get the log level for the ensemble test.
     * @return The log level. */
    BCLog::LogLevel GetLogLevel()
    { return fLogLevel; };

    /**
     * Set the log level for the ensemble test.
     * @param level The log level. */
    void SetLogLevel(BCLog::LogLevel level)
    { fLogLevel = level; };

    /**
     * Perform the full set of single channel analyses and the
     * combination. Possible options are: \n
     * "nosyst" : ignore systematic uncertainties.
     * "mcmc" : use mcmc.
     * @param dirname The name of a directory into which the results are copied.
     * @param options A set of options.
     * @return An error code. */
    int PerformSingleChannelAnalyses(const std::string& dirname, const std::string& options = "");

    /**
     * Perform the analysis using one systematic at a time, without
     * systematic and with all systematics. The following options
     * are available: \n
     * "mcmc" : use mcmc.
     * @param dirname The name of a directory into which the results are copied.
     * @param options A set of options.
     * @return An error code. */
    int PerformSingleSystematicAnalyses(const std::string& dirname, const std::string& options = "");

    /**
     * Perform the analysis on pseudo-data generated by varying one
     * of the parameters.
     * @param dirname The name of a directory into which the results are copied.
     * @param default_parameters The set of parameters which are fixed.
     * @param index The index of the parameter which will be varied.
     * @param parametervalues The different values of the parameter which is varied.
     * @param nesembles The number of ensembles used in the test.
     * @return An error code. */
    int PerformCalibrationAnalysis(const std::string& dirname, const std::vector<double>& default_parameters, int index, const std::vector<double>& parametervalues, int nensembles = 1000);

    /**
     * Build a single ensemble based on a single set of parameters.
     * @param parameters The set of parameters which are used to generate the ensembles.
     * @param options A set of options: \n
     * "data" : all pseudo data sets are equal to the actual data set
     * @return A vector of TH1D histograms with the pseudo-data. */
    std::vector<TH1D> BuildEnsemble(const std::vector<double>& parameters, const std::string& options = "");

    /**
     * Build ensembles based on a single set of parameters.
     * @param parameters The set of parameters which are used to generate the ensembles.
     * @param ensembels The number of ensembles to be generated.
     * @param options A set of options: \n
     * "data" : all pseudo data sets are equal to the actual data set
     * @return A tree containing the ensembles. */
    TTree* BuildEnsembles(const std::vector<double>& parameters, int nensembles, const std::string& options = "");

    /**
     * Build ensembles based on a varying sets of parameters, e.g., using the prior or posterior.
     * @param tree A BAT output tree containing the parameters to be used for the generation of the ensembles.
     * @param ensembels The number of ensembles to be generated.
     * @param options A set of options: \n
     * "data" : all pseudo data sets are equal to the actual data set
     * @return A tree containing the ensembles. */
    TTree* BuildEnsembles(TTree* tree, int nensembles, const std::string& options = "");

    /**
     * Perform ensemble test based on one set of parameters.
     * @param parameters The set of parameters which are used to generate the ensembles.
     * @param ensembels The number of ensembles to be generated.
     * @param options A set of options: \n
     * "MC" : for each ensemble, the template are fluctuated statistically \n
     * "data" : all pseudo data sets are equal to the actual data set
     * @return A tree containing the ensembles and the output of the test. */
    TTree* PerformEnsembleTest(const std::vector<double>& parameters, int nensembles, const std::string& options = "");

    /**
     * Perform ensemble test based on varying sets of parameters.
     * @param tree A BAT output tree containing the parameters to be used for the generation of the ensembles.
     * @param nensembles The number of ensembles to be generated.
     * @param nstart The first ensemble used in the tree.
     * @param options A set of options: \n
     * "MC" : for each ensemble, the template are fluctuated statistically \n
     * "data" : all pseudo data sets are equal to the actual data set
     * @return A tree containing the ensembles and the output of the test. */
    TTree* PerformEnsembleTest(TTree* tree, int nensembles, int start = 0, const std::string& options = "");

    /**
     * Transform a matrix to a set of histograms.
     * @param matrix The matrix.
     * @return A vector of histograms. */
    std::vector<TH1D> MatrixToHistograms(const std::vector< std::vector<double> >& matrix);

private:

    /**
     * The MTF object. */
    BCMTF* fMTF;

    /**
     * A random number generator. */
    TRandom3* fRandom;

    /**
     * A flag defining the use of marginalization for the analyses. */
    bool fFlagMarginalize;

    /**
     * The log level for the ensemble tests. */
    BCLog::LogLevel fLogLevel;

};
// ---------------------------------------------------------

#endif

