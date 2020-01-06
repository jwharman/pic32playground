#include <stdint.h>
#include "user_timer.h"
#include "system_tick.h"

uint32_t user_timer_get_tick(void)
{
    return get_sys_tick();
}

uint32_t user_timer_setpoint (uint32_t delay)
{
    //the set_point is returned
    uint32_t set;
    set = (get_sys_tick())+(delay-1);      //make next alarm time
    if (0 == set) //set alarm to time+delay unless 0
    {
        set++;
    }
    return (set);                    //return next alarm time
}

uint32_t user_timer_get_setpoint (uint32_t timestamp, uint32_t time)
{
    //this returns the timer setpoint given the timestamp passed in, instead of the system clock
    //the set_point is returned
    uint32_t set;

    set = timestamp + (time-1);  //make next alarm time
    if (0 == set)                 //set alarm to time+delay unless 0
    {
        set = 1;
    }

    return (set);              //return next alarm time

}

uint32_t user_timer_expired_setpoint (void)
{
    //this function is similar to user_timer_setpoint,
    //this is used when an we want to obtain a new timestamp setpoint value that will ensure that we
    //always are in a timer expired condition.  For example, if a message has timed out
    //the timestamp value has to be updated in order to keep the timer rollover from
    //eventually resetting our stale time
    uint32_t set = (get_sys_tick())-1;
    if (0 == set)
    {
        set--;
    }
    return (set);
}

uint32_t user_timer_set_expired_setpoint (uint32_t time)
{

    //this function is similar to user_timer_setpoint,
    //this is used when an we want to obtain a new timestamp value that will ensure that we
    //always are in a timer expired condition.  For example, if a message has timed out
    //the timestamp value has to be updated in order to keep the timer rollover from
    //eventually resetting our stale time
    uint32_t set = (get_sys_tick())-(time+1);
    if (0 == set)
    {
        set--;
    }
    return (set);
}

uint32_t user_timer_start_expired (user_tmr * user_tmr_ptr)
{
    //this function starts the timer and uses an expired time as its setpoint
    user_tmr_ptr->set_point = user_timer_expired_setpoint();
    user_tmr_ptr->enabled = 1;

    return (user_tmr_ptr->set_point);
}

uint32_t user_timer_start (user_tmr * user_tmr_ptr, uint32_t time)
{

    //the set_point is returned
    uint32_t set;

    set = user_timer_setpoint(time);  //make next alarm time

    //set our structure with the proper values
    user_tmr_ptr->set_point = set;
    user_tmr_ptr->enabled = 1;

    return (set);                    //return next alarm time

}

uint32_t user_timer_expired (uint32_t set_point)
{
    //returns true if time has expired exceeded, handles wrap
    uint32_t ret = 0;

    if (!set_point)
    {
        ret = 1;
    }
    else
    {
        ret = ((set_point-(get_sys_tick()))&0x8000);       //return true if time expired
    }

    return ret;
}

uint32_t user_timer_done (user_tmr * user_tmr_ptr)
{
    //this auto clears the 'enabled' structure.
    //return:  0 = not expired, else expired
    uint32_t ret = 0;
    
    if (user_tmr_ptr->enabled > 0)
    {
        ret = user_timer_expired(user_tmr_ptr->set_point);
        if (ret>0)
        {
            user_tmr_ptr->enabled = 0;
        }
    }

    return ret;
}

uint32_t user_timer_interval (user_tmr * user_tmr_ptr, uint32_t interval)
{
    //when using an interval, this does everything, just initialize the user_tmr variable first
    //return:  0 = interval not expired, else expired
    uint32_t ret = 0;
    if (user_tmr_ptr->enabled==0)
    {
        user_timer_start(user_tmr_ptr, interval);
    }
    else if (user_timer_done(user_tmr_ptr))
    {
        ret = 1;
    }

    return ret;
}

uint32_t debounce (uint32_t input, input_state * is, uint32_t time)
{

    //compare the pins current value to the last value
    if (input!=is->prev_value)
    {
        //the pins state has changed, so start the polling all over again
        user_timer_start(&is->tmr, time);
    }
    else
    {
        if (1 == is->tmr.enabled)
        {
            //check for expired timer
            if (user_timer_done(&is->tmr))
            {
                is->state = input;
            }
        }
    }

    //keep track of the last value
    is->prev_value = input;

    //return the state
    return is->state;

}

uint32_t delay_on (uint32_t input, input_state * is, uint32_t time)
{
    //immediate OFF, delayed ON...
    if (input)
    {
        if (1 == is->tmr.enabled)
        {
            //check for expired timer
            if (user_timer_done(&is->tmr))
            {
                is->state = 1;
            }

        }
        else if (0 == is->state)
        {
            //start the timer
            user_timer_start(&is->tmr, time);
        }

    }
    else
    {
        is->tmr.enabled = 0;
        is->state = 0;
    }

    //return the state
    return is->state;

}

uint32_t delay_off (uint32_t input, input_state * is, uint32_t time)
{

    //immediate ON, delayed OFF...
    if (0 == input)
    {
        if (1 == is->tmr.enabled)
        {
            //check for expired timer
            if (user_timer_done(&is->tmr))
            {
                is->state = 0;
            }
        }
        else if (1 == is->state)
        {
            //start the timer
            user_timer_start(&is->tmr, time);
        }
    }
    else
    {
        is->tmr.enabled = 0;
        is->state = 1;
    }

    //return the state
    return is->state;
}
