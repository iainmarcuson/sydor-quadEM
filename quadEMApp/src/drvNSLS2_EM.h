/*
 * drvNSLS2_EM.h
 * 
 * Asyn driver that inherits from the drvQuadEM class to control the NSLS2 electrometer / XBPM
 *
 * Author: Mark Rivers, Pete Siddons
 *
 * Created January 18th, 2016
 */

#include "drvQuadEM.h"
#include "pl_lib.h"

#define MAX_COMMAND_LEN 256
#define MAX_MODULES 1
#define MAX_PORTNAME_LEN 32
#define MAX_RANGES 5

/** Class to control the NSLS Precision Integrator */
class drvNSLS2_EM : public drvQuadEM {
public:
    drvNSLS2_EM(const char *portName, int moduleID, int ringBufferSize);
    
    /* These are the methods we implement from asynPortDriver */
    void report(FILE *fp, int details);
                 
    /* These are the methods that are new to this class */
    virtual void exitHandler();

protected:
    /* These are the methods we implement from quadEM */
    virtual asynStatus setAcquire(epicsInt32 value);
    virtual asynStatus setRange(epicsInt32 value);
    virtual asynStatus setAveragingTime(epicsFloat64 value);  
    virtual asynStatus setValuesPerRead(epicsInt32 value);
    virtual asynStatus setBiasVoltage(epicsFloat64 value);
    virtual asynStatus readStatus();
    virtual asynStatus reset();
 
private:
    /* Our data */
    double ranges_[MAX_RANGES];
    epicsFloat64 rawData_[QE_MAX_INPUTS];
    int readingsAveraged_;
    int readingActive_;
    int firmwareVersion_;
    volatile unsigned int *fpgabase;  //mmap'd fpga registers

    /* our functions */
    asynStatus getFirmwareVersion();
    void callbackFunc();
    int readMeter(int *adcbuf);
    void mmap_fpga();
};

