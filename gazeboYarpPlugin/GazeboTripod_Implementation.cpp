/*
* Copyright (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
* Authors: Alberto Cardellino
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*
*/

#include "GazeboTripodMotionControl.h"
#include <yarp/os/LogStream.h>

using namespace yarp::dev;
using namespace cer::dev;


    // AXIS IAxisInfo
bool GazeboTripodMotionControl::getAxisName(int axis, yarp::os::ConstString& name)
{
    if (axis < 0 || axis >= (int)m_numberOfJoints) return false;
    name =  yarp::os::ConstString(controlboard_joint_names.at(axis));
    return true;
}


    //ENCODERS
bool GazeboTripodMotionControl::getEncoder(int j, double* v)
{
    if (v && j >= 0 && j < (int)m_numberOfJoints)
    {
        *v = m_last_motorElongat[j];
        return true;
    }
    return false;
}

bool GazeboTripodMotionControl::getEncoders(double* encs)
{
    if (!encs) return false;
    for(int j=0; j<m_numberOfJoints; j++)
        encs[j] =  m_last_motorElongat[j];
    return true;
}

bool GazeboTripodMotionControl::resetEncoder(int j)
{
    if (j >= 0 && j < (int)m_numberOfJoints)
    {
        m_zeroPosition[j] = m_positions[j];
        // TODO: check if iKin is required here or not
        return true;
    }
    return false;
}

bool GazeboTripodMotionControl::resetEncoders()
{
    for (unsigned int i=0; i<m_numberOfJoints; ++i)
    {
        m_zeroPosition[i] = m_positions[i];
        // TODO: check if iKin is required here or not
    }
    return true;
}


bool GazeboTripodMotionControl::setEncoder(int j, double val)
{
    if (j >= 0 && j < (int)m_numberOfJoints)
    {
        m_zeroPosition[j] = m_positions[j]-val;
        // TODO: check if iKin is required here or not
        return true;
    }
    return false;
}


bool GazeboTripodMotionControl::setEncoders(const double* vals)
{
    for (unsigned int i=0; i<m_numberOfJoints; ++i)
    {
        m_zeroPosition[i] = m_positions[i]-vals[i];
        // TODO: check if iKin is required here or not
    }
    return true;
}


bool GazeboTripodMotionControl::getEncoderSpeed(int j, double* sp)
{
    if (sp && j >= 0 && j < (int)m_numberOfJoints) {
        *sp = m_velocities[j];
        return true;
    }
    return false;
}

bool GazeboTripodMotionControl::getEncoderSpeeds(double* spds)
{
//     return NOT_YET_IMPLEMENTED("getEncoderSpeeds");
    return false;
}


bool GazeboTripodMotionControl::getEncoderAcceleration(int j, double* spds)
{
//     return NOT_YET_IMPLEMENTED("getEncoderAcceleration");
    return false;
}

bool GazeboTripodMotionControl::getEncoderAccelerations(double* accs)
{
//     return NOT_YET_IMPLEMENTED("getEncoderAccelerations");
    return false;
}


    // ENCODERS TIMED
bool GazeboTripodMotionControl::getEncodersTimed(double* encs, double* time)
{
    double my_time = m_lastTimestamp.getTime();
    for (unsigned int i = 0; i <m_numberOfJoints; ++i)
    {
        encs[i] = m_last_motorElongat[i];
        time[i] = my_time;
    }
    return true;
}

bool GazeboTripodMotionControl::getEncoderTimed(int j, double* encs, double* time)
{
    if (time && encs && j >= 0 && j < (int)m_numberOfJoints)
    {
        *encs = m_last_motorElongat[j];
        *time = m_lastTimestamp.getTime();
        return true;
    }
    return false;
}


    //POSITION CONTROL
bool GazeboTripodMotionControl::stop(int j)
{
    if (j >= 0 && j < (int)m_numberOfJoints)
    {
        m_trajectoryGenerationReferencePosition[j] = m_positions[j];
        // TODO: check if iKin is required here or not
        return true;
    }
    return false;
}

bool GazeboTripodMotionControl::stop()
{
    m_trajectoryGenerationReferencePosition = m_positions;
    // TODO: check if iKin is required here or not
    return true;
}

bool GazeboTripodMotionControl::positionMove(int j, double ref)
{
    NOT_YET_IMPLEMENTED("positionMove");
    return false;

//     if (j >= 0 && j < (int)m_numberOfJoints)
//     {
//         m_trajectoryGenerationReferencePosition[j] = ref; //we will use this m_trajectoryGenerationReferencePosition in the next simulation onUpdate call to ask gazebo to set PIDs m_trajectoryGenerationReferencePosition to this value
//         // TODO: call iKi
//         return true;
//     }
//     return false;
}

bool GazeboTripodMotionControl::getAxes(int* ax)
{
    if (!ax) return false;
    *ax = m_numberOfJoints;
    return true;
}

 // WORKS
bool GazeboTripodMotionControl::positionMove(const double* refs)
{
    NOT_YET_IMPLEMENTED("positionMove");
    return false;

//     for (unsigned int i = 0; i < m_numberOfJoints; ++i) {
//         m_trajectoryGenerationReferencePosition[i] = refs[i];
//     }
//     return true;
}

    /// @arg sp [deg/sec]
bool GazeboTripodMotionControl::setRefSpeed(int j, double sp)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect. No need for speed here.
    // (btw: not the game, that's cool anyway)
    return NOT_YET_IMPLEMENTED("setRefSpeed");
}

bool GazeboTripodMotionControl::getRefSpeed(int j, double* ref)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect. No need for speed here.
    // (btw: not the game, that's cool anyway)
    return NOT_YET_IMPLEMENTED("setRefSpeed");
}

bool GazeboTripodMotionControl::getRefSpeeds(double* spds)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect. No need for speed here.
    // (btw: not the game, that's cool anyway)
    return NOT_YET_IMPLEMENTED("setRefSpeed");
}


bool GazeboTripodMotionControl::relativeMove(int j, double delta)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect.
    // Is this useful here??
    return NOT_YET_IMPLEMENTED("relativeMove");
}

bool GazeboTripodMotionControl::relativeMove(const double* deltas)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect.
    // Is this useful here??
    return NOT_YET_IMPLEMENTED("relativeMove");
}

bool GazeboTripodMotionControl::checkMotionDone(int j, bool* flag)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect.
    // CheckMotionDone, is useful only in positionMode
//     return NOT_YET_IMPLEMENTED("checkMotionDone");
    return true;
}

bool GazeboTripodMotionControl::checkMotionDone(bool* flag)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect.
    // CheckMotionDone, is useful only in positionMode
//     return NOT_YET_IMPLEMENTED("checkMotionDone");
    return true;
}

bool GazeboTripodMotionControl::setPositionMode()
{
    // This device should support only positionDirect and maybe velocity
    return NOT_YET_IMPLEMENTED("checkMotionDone");
}


    // Position Control 2
bool GazeboTripodMotionControl::positionMove(const int n_joint, const int* joints, const double* refs)
{
    // This device should support only positionDirect and maybe velocity
    return NOT_YET_IMPLEMENTED("positionMove");
}

bool GazeboTripodMotionControl::relativeMove(const int n_joint, const int* joints, const double* deltas)
{
    // This device should support only positionDirect and maybe velocity
    return NOT_YET_IMPLEMENTED("relativeMove");
}

bool GazeboTripodMotionControl::checkMotionDone(const int n_joint, const int* joints, bool* flags)
{
    // TODO: Verify: this device is suppose to get elongations and convert to angles,
    // to it'll be basically controlled in positionDirect.
    // CheckMotionDone, is useful only in positionMode
    return NOT_YET_IMPLEMENTED("checkMotionDone");
}

bool GazeboTripodMotionControl::setRefSpeeds(const int n_joint, const int* joints, const double* spds)
{
    return NOT_YET_IMPLEMENTED("setRefSpeeds");
}

bool GazeboTripodMotionControl::setRefAccelerations(const int n_joint, const int* joints, const double* accs)
{
    return NOT_YET_IMPLEMENTED("setRefAccelerations");

}

bool GazeboTripodMotionControl::getRefSpeeds(const int n_joint, const int *joints, double *spds)
{
    return NOT_YET_IMPLEMENTED("getRefSpeeds");

}

bool GazeboTripodMotionControl::getRefAccelerations(const int n_joint, const int *joints, double *accs)
{
    return NOT_YET_IMPLEMENTED("getRefAccelerations");

}

bool GazeboTripodMotionControl::stop(const int n_joint, const int *joints)
{
    return NOT_YET_IMPLEMENTED("stop - group");
}


    /// @arg spds [deg/sec]
bool GazeboTripodMotionControl::setRefSpeeds(const double *spds)
{
    return NOT_YET_IMPLEMENTED("setRefSpeeds");
}


bool GazeboTripodMotionControl::setRefAcceleration(int j, double acc)
{
    return NOT_YET_IMPLEMENTED("setRefAccelerationp");
}

bool GazeboTripodMotionControl::setRefAccelerations(const double *accs)
{
    return NOT_YET_IMPLEMENTED("setRefAccelerations");
}

bool GazeboTripodMotionControl::getRefAcceleration(int j, double *acc)
{
    return NOT_YET_IMPLEMENTED("getRefAcceleration");
}

bool GazeboTripodMotionControl::getRefAccelerations(double *accs)
{
    return NOT_YET_IMPLEMENTED("getRefAccelerations");
}


    //VELOCITY CONTROL 2
bool GazeboTripodMotionControl::setVelocityMode()
{
    return NOT_YET_IMPLEMENTED("setVelocityMode");
}

bool GazeboTripodMotionControl::velocityMove(int j, double sp)
{
    return NOT_YET_IMPLEMENTED("velocityMove");
}

bool GazeboTripodMotionControl::velocityMove(const double *sp)
{
    return NOT_YET_IMPLEMENTED("velocityMove");
}

bool GazeboTripodMotionControl::velocityMove(const int n_joint, const int *joints, const double *spds)
{
    return NOT_YET_IMPLEMENTED("velocityMove");
}


bool GazeboTripodMotionControl::setVelPid(int j, const yarp::dev::Pid &pid)
{
    return NOT_YET_IMPLEMENTED("setVelPid");
}

bool GazeboTripodMotionControl::setVelPids(const yarp::dev::Pid *pids)
{
    return NOT_YET_IMPLEMENTED("setVelPids");
}

bool GazeboTripodMotionControl::getVelPid(int j, yarp::dev::Pid *pid)
{
    return NOT_YET_IMPLEMENTED("getVelPid");
}

bool GazeboTripodMotionControl::getVelPids(yarp::dev::Pid *pids)
{
    return NOT_YET_IMPLEMENTED("getVelPids");
}


    //CONTROL MODE
bool GazeboTripodMotionControl::setPositionMode(int j)
{
    return NOT_YET_IMPLEMENTED("setPositionMode");
}

bool GazeboTripodMotionControl::setVelocityMode(int j)
{
    return NOT_YET_IMPLEMENTED("setVelocityMode");
}

bool GazeboTripodMotionControl::getControlMode(int j, int *mode)
{
    if (!mode || j < 0 || j >= (int)m_numberOfJoints)
        return false;
    *mode = m_controlMode[j];
    return true;
}

bool GazeboTripodMotionControl::setTorqueMode(int j)
{
    return NOT_YET_IMPLEMENTED("setTorqueMode");
}

bool GazeboTripodMotionControl::getControlModes(int *modes)
{
    if (!modes) return false;
    for(unsigned int j = 0; j < m_numberOfJoints; ++j) {
        modes[j] = m_controlMode[j];
    }
    return true;
}

bool GazeboTripodMotionControl::setImpedancePositionMode(int j)
{
    return NOT_YET_IMPLEMENTED("setImpedancePositionMode");
}

bool GazeboTripodMotionControl::setImpedanceVelocityMode(int j)
{
    return NOT_YET_IMPLEMENTED("setImpedanceVelocityMode");
}

bool GazeboTripodMotionControl::setOpenLoopMode(int j)
{
    return NOT_YET_IMPLEMENTED("setOpenLoopMode");
}

    // CONTROL MODE 2
bool GazeboTripodMotionControl::getControlModes(const int n_joint, const int *joints, int *modes)
{
    bool ret = true;
    for (int i = 0; i < n_joint; i++)
        ret = ret && getControlMode(joints[i], &modes[i]);
    return ret;
}

bool GazeboTripodMotionControl::setControlMode(const int j, const int mode)
{
    bool ret = true;
    // mode specific switching actions
    switch (mode)
    {
        case VOCAB_CM_POSITION_DIRECT :
            m_referencePositions[j] = m_positions[j];
            m_trajectoryGenerationReferencePosition[j] = m_positions[j];
            ret = true;
        break;
        case VOCAB_CM_POSITION :
        case VOCAB_CM_VELOCITY :
        case VOCAB_CM_TORQUE :
        case VOCAB_CM_OPENLOOP :
        default :
            yError() << "Mode " << yarp::os::Vocab::decode(mode) << " is not yet implemented for GazeboTripodMotionControl";
            ret = false;
        break;
    }
    return ret;
}

bool GazeboTripodMotionControl::setControlModes(const int n_joint, const int *joints, int *modes)
{
    bool ret = true;
    for (int i = 0; i < n_joint; i++)
        ret = ret && setControlMode(joints[i], modes[i]);
    return ret;
}

bool GazeboTripodMotionControl::setControlModes(int *modes)
{
    bool ret = true;
    for (int i = 0; i < (int)m_numberOfJoints; i++)
        ret = ret && setControlMode(i, modes[i]);
    return ret;
}

    // CONTROL LIMITS2 (inside comanOthers.cpp)
bool GazeboTripodMotionControl::getLimits(int axis, double *min, double *max)
{
    std::cout << "Limits for joint " << axis << "are: min " << m_jointLimits[axis].min << ", max: " <<  m_jointLimits[axis].max << std::endl;;
    if (axis < 0 || axis >= (int)m_numberOfJoints) return false;
    if (!min || !max) return false;
    *min = m_jointLimits[axis].min;
    *max = m_jointLimits[axis].max;
    return true;
}

bool GazeboTripodMotionControl::setLimits(int axis, double min, double max)
{
    if (axis < 0 || axis >= (int)m_numberOfJoints) return false;
    m_jointLimits[axis].max = max;
    m_jointLimits[axis].min = min;
    return true;
}

bool GazeboTripodMotionControl::getVelLimits(int axis, double *min, double *max)
{
    return NOT_YET_IMPLEMENTED("getVelLimits");
}

bool GazeboTripodMotionControl::setVelLimits(int axis, double min, double max)
{
    return NOT_YET_IMPLEMENTED("getVelLimits");
}


// IPOSITION DIRECT
bool GazeboTripodMotionControl::setPositionDirectMode()
{
    bool ret = true;
    for (int j = 0; j < (int)m_numberOfJoints; j++)
    {
        ret = ret && this->setControlMode(j, VOCAB_CM_POSITION_DIRECT);
    }
    return ret;
}

bool GazeboTripodMotionControl::setPosition(int j, double ref)
{
    if (m_controlMode[j] == VOCAB_CM_POSITION_DIRECT)
    {
        if (j >= 0 && j < (int)m_numberOfJoints)
        {
            m_referenceElongations[j] = ref;
            tripod_client2Sim(m_referenceElongations, m_referencePositions);
            yInfo() << "setpositions: elongations are " << m_referenceElongations.toString() << "\n\t positions are " << m_referencePositions.toString();
            return true;
        }
    } else
    {
        std::cerr << "[WARN] GazeboTripodMotionControl: you tried to call setPosition" << std::endl;
        std::cerr << "[WARN] for a joint that is not in POSITION_DIRECT control mode." << std::endl;
    }
    return false;
}

bool GazeboTripodMotionControl::setPositions(const int n_joint, const int *joints, double *refs)
{
    for (int i = 0; i < n_joint; i++)
    {
        m_referenceElongations[i] = refs[i];
    }
    tripod_client2Sim(m_referenceElongations, m_referencePositions);
    yInfo() << "setpositions: elongations are " << m_referenceElongations.toString() << "\n\t positions are " << m_referencePositions.toString();
    return true;
}

bool GazeboTripodMotionControl::setPositions(const double *refs)
{
    for (int i = 0; i < m_numberOfJoints; i++)
    {
        m_referenceElongations[i] = refs[i];
    }
    tripod_client2Sim(m_referenceElongations, m_referencePositions);
    yInfo() << "setpositions: elongations are " << m_referenceElongations.toString() << "\n\t positions are " << m_referencePositions.toString();
    return true;
}