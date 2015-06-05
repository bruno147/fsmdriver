#ifndef straightLine
#define FSMDRIVER5_H

#include "FSM.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "Log.h"

#include <vector>
#include <bitset>

/** A controller with a 5-state FSM.
 *
 * @todo describe class.
 * @todo document attributes, fix attribute names (no caps-only).
 * @todo document methods */
class FSMDriver5 : public FSMDriver {
private:
    StraightLine straightLine;
    ApproachingCurve approachingCurve;
    Curve curve;
    OutOfTrack outOfTrack;
    Stuck stuck;

    int segment_id;

    int MAX_STRAIGHT_LINE_VAR;
    int MIN_STRAIGHT_LINE_VAR;
    int MAX_APPROACHING_CURVE_VAR;
    int MIN_APPROACHING_CURVE_VAR;

    float binToFloat (string bits);
    unsigned int binToUsignedInt (string bits);

    std::string getArgument(int i, char** argv);

    float    parameters[22];/**Driver parameters,it can be fixed or set by Genetic Algorithm*/

public:
    virtual void onShutdown();
    virtual void onRestart();

    /** Initialization of the desired angles for the range finders. */
    virtual void init(float *angles);

    FSMDriver5();
    FSMDriver5(int, char**);
    virtual ~FSMDriver5();

    /** Transitions between states (if appropriate).
     * @todo fix documentation. */
    void transition(CarState &);
};

#endif // FSMDriver5_H
