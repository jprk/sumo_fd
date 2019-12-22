/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    MSStageTranship.h
/// @author  Melanie Weber
/// @author  Andreas Kendziorra
/// @date    Thu, 12 Jun 2014
///
// The class for modelling container-movements
/****************************************************************************/
#pragma once

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <string>
#include <vector>
#include <set>
#include <utils/common/SUMOTime.h>
#include <utils/common/Command.h>
#include <utils/geom/Position.h>
#include <utils/geom/PositionVector.h>
#include <microsim/transportables/MSTransportable.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MSNet;
class MSEdge;
class MSLane;
class OutputDevice;
class SUMOVehicleParameter;
class MSStoppingPlace;
class SUMOVehicle;
class MSVehicleType;
class MSCModel_NonInteracting;
class CState;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * A "real" stage performing the tranship of a container
 * A container is in this stage if it gets transhiped between two stops that are
 * assumed to be connected.
 */
class MSStageTranship : public MSStageMoving {

public:
    /// constructor
    MSStageTranship(const std::vector<const MSEdge*>& route, MSStoppingPlace* toStop, double speed, double departPos, double arrivalPos);

    /// destructor
    ~MSStageTranship();

    MSStage* clone() const;

    /// proceeds to the next step
    virtual void proceed(MSNet* net, MSTransportable* transportable, SUMOTime now, MSStage* previous);

    /// @brief get travel distance in this stage
    double getDistance() const;

    /// Returns the current stage description as a string
    std::string getStageDescription(const bool isPerson) const {
        UNUSED_PARAMETER(isPerson);
        return "tranship";
    }
    std::string getStageSummary(const bool isPerson) const;

    /** @brief Called on writing tripinfo output
     * @param[in] os The stream to write the information into
     * @exception IOError not yet implemented
     */
    virtual void tripInfoOutput(OutputDevice& os, const MSTransportable* const transportable) const;

    /** @brief Called on writing vehroute output
     * @param[in] os The stream to write the information into
     * @exception IOError not yet implemented
     */
    virtual void routeOutput(const bool isPerson, OutputDevice& os, const bool withRouteLength) const;

    /// @brief move forward and return whether the container arrived
    bool moveToNextEdge(MSTransportable* container, SUMOTime currentTime, MSEdge* nextInternal = 0);


    /// @brief the maximum speed of the transportable
    inline double getMaxSpeed(const MSTransportable* const transportable=nullptr) const {
        UNUSED_PARAMETER(transportable);
        return mySpeed;
    }

    inline double getArrivalPos() const {
        return myArrivalPos;
    }

    inline const MSEdge* getNextRouteEdge() const {
        return myRouteStep == myRoute.end() - 1 ? 0 : *(myRouteStep + 1);
    }

private:
    /// @brief Invalidated copy constructor.
    MSStageTranship(const MSStageTranship&);

    /// @brief Invalidated assignment operator.
    MSStageTranship& operator=(const MSStageTranship&);

};


/****************************************************************************/