#include <iostream>
#include <cstdlib>
#include "InterestOperator.h"
#include "InterestOperatorFactory.h"
#include "MoravecOperator.h"
#include "Chip.h"
#include "Cube.h"
#include "Pvl.h"
#include "PvlGroup.h"
#include "PvlObject.h"
#include "Preference.h"
#include "UniversalGroundMap.h"

using namespace Isis;

int main() {
  Isis::Preference::Preferences(true);

  try {
    PvlGroup op("Operator");
    op += PvlKeyword("Name", "Moravec");
    op += PvlKeyword("DeltaSamp", "100");
    op += PvlKeyword("DeltaLine", "100");
    op += PvlKeyword("Samples", "15");
    op += PvlKeyword("Lines", "15");
    op += PvlKeyword("MinimumDN", "0.0");
    op += PvlKeyword("MaximumDN", "1.0");
    op += PvlKeyword("MinimumInterest", "0.0");

    PvlGroup opv("ValidMeasure"); 
    opv += PvlKeyword("MinDN", "0.0");
    opv += PvlKeyword("MaxDN", "1.0");
    opv += PvlKeyword("MinEmission", "15.0");
    opv += PvlKeyword("MaxEmission", "25.0");
    opv += PvlKeyword("MinIncidence", "0.0");
    opv += PvlKeyword("MaxIncidence", "135.0");

    PvlObject o("InterestOperator");
    o.addGroup(op);
    o.addGroup(opv);

    Pvl pvl;
    pvl.addObject(o);
    std::cout << pvl << std::endl;

    InterestOperator *iop = InterestOperatorFactory::Create(pvl);

    Cube c;
    c.open("$ISISTESTDATA/isis/src/mgs/unitTestData/ab102401.cub");

    //iop->Operate(c, 100, 350);
    UniversalGroundMap univGrndMap(c);
    iop->Operate(c,  univGrndMap, 100, 350);

    std::cout << "Sample: " << iop->CubeSample() << std::endl
              << "Line : " << iop->CubeLine() << std::endl
              << "Interest: " << iop->InterestAmount() << std::endl;
  }
  catch(IException &e) {
    e.print();
  }

  return 0;
}
