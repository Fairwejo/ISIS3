#ifndef AlternativeTestCsmModel_h
#define AlternativeTestCsmModel_h

#include <string>

#include "csm/Plugin.h"
#include "csm/GeometricModel.h"
#include "csm/Version.h"

/**
 * An alternative Test CSM (Community Sensor Model) Sensor Model used to test 
 * CSM sensor model support in ISIS. This can be used to help test situations 
 * where multiple potential sensor models can be constructed, or to make sure 
 * that specific sensor model requirements are being met.  
 * 
 * @author 2020-12-08 Kristin Berry
 */
class AlternativeTestCsmModel : public csm::GeometricModel {
  public:
    // Static variables that describe the model
    static const std::string SENSOR_MODEL_NAME;
    static const std::vector<std::string> PARAM_NAMES;
    static const std::vector<std::string> PARAM_UNITS;
    static const std::vector<csm::param::Type> PARAM_TYPES;
    static const std::vector<csm::SharingCriteria> PARAM_SHARING_CRITERIA;

    AlternativeTestCsmModel();
    ~AlternativeTestCsmModel();
    // csm::Model methods
    std::string getFamily() const;
    csm::Version getVersion() const;
    std::string getModelName() const;
    std::string getPedigree() const;
    std::string getImageIdentifier() const;
    void setImageIdentifier(const std::string& imageId,
                            csm::WarningList* warnings = NULL);
    std::string getSensorIdentifier() const;
    std::string getPlatformIdentifier() const;
    std::string getCollectionIdentifier() const;
    std::string getTrajectoryIdentifier() const;
    std::string getSensorType() const;
    std::string getSensorMode() const;
    std::string getReferenceDateAndTime() const;
    std::string getModelState() const;
    void replaceModelState(const std::string& argState);
    std::string constructStateFromIsd(const csm::Isd stringIsd);
    // csm::GeometricModel methods
    csm::EcefCoord getReferencePoint() const;
    void setReferencePoint(const csm::EcefCoord& groundPt);
    int getNumParameters() const;
    std::string getParameterName(int index) const;
    std::string getParameterUnits(int index) const;
    bool hasShareableParameters() const;
    bool isParameterShareable(int index) const;
    csm::SharingCriteria getParameterSharingCriteria(int index) const;
    double getParameterValue(int index) const;
    void setParameterValue(int index, double value);
    csm::param::Type getParameterType(int index) const;
    void setParameterType(int index, csm::param::Type pType);
    double getParameterCovariance(int index1,
                                  int index2) const;
    void setParameterCovariance(int index1,
                                int index2,
                                double covariance);
    int getNumGeometricCorrectionSwitches() const;
    std::string getGeometricCorrectionName(int index) const;
    void setGeometricCorrectionSwitch(int index,
                                      bool value,
                                      csm::param::Type pType);
    bool getGeometricCorrectionSwitch(int index) const;
    std::vector<double> getCrossCovarianceMatrix(
          const csm::GeometricModel& comparisonModel,
          csm::param::Set pSet = csm::param::VALID,
          const csm::GeometricModel::GeometricModelList& otherModels = GeometricModel::GeometricModelList()) const;

  private:
    std::string m_modelState;
    std::vector<double> m_param_values;
};
#endif
