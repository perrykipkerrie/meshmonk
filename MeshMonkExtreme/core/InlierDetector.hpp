#ifndef INLIERDETECTOR_HPP
#define INLIERDETECTOR_HPP

#include <Eigen/Dense>
#include <stdio.h>
#include <iostream>
#include <map>
#include <boost/variant.hpp> //make sure you have boost: http://stackoverflow.com/questions/12241152/boost-no-such-file-or-directory
#include "../global.hpp"

typedef Eigen::VectorXf VecDynFloat;
typedef Eigen::Matrix< float, Eigen::Dynamic, registration::NUM_FEATURES> FeatureMat; //matrix Mx6 of type float
typedef Eigen::Matrix< float, 1, registration::NUM_FEATURES> FeatureVec; //matrix Mx6 of type float
typedef Eigen::Vector3f Vec3Float;
typedef boost::variant<int, float, bool, std::string> ParameterType;
typedef std::map<std::string, ParameterType> DictionaryType;

namespace registration {

class InlierDetector
{
    /*
    # GOAL
    Determine which elements are inliers ('normal') and which are outliers
    ('abnormal'). There are different ways to to that, but they should all
    result in a scalar assigmnent that represents the probability of an element
    being an inlier.

    # INPUTS
    -_inFeatures
    -_inCorrespondingFeatures
    -_inCorrespondingFlags

    # PARAMETERS
    -_kappa(=3): Mahalanobis distance that determines cut-off in- vs outliers

    # OUTPUTS
    -_ioProbability

    # RETURNS
    */

    private:
        //# Inputs
        const FeatureMat * _inFeatures = NULL;
        const FeatureMat * _inCorrespondingFeatures = NULL;
        const VecDynFloat * _inCorrespondingFlags = NULL;

        //# Outputs
        VecDynFloat *_ioProbability = NULL;

        //# User Parameters
        DictionaryType _parameterList;
        float _kappa = 3.0;

        //# Internal variables
        size_t _numElements;

    protected:

    public:
        void set_input(const FeatureMat * const inFeatures,
                        const FeatureMat * const inCorrespondingFeatures,
                        const VecDynFloat * const inCorrespondingFlags);
        void set_output(VecDynFloat * const _ioProbability);
        void set_parameters(const float kappa);
        void update();
};

} //namespace registration

#endif
