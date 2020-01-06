/* 
 * File:   user_timer.h
 * Author: Jacob
 *
 * Created on March 2, 2019, 6:44 PM
 */

#ifndef USER_TIMER_H
#define	USER_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct user_tmr_t {
    uint32_t  set_point;       //how many ms before resetting.
    uint32_t enabled;          //signifies whether the timer is running or not...
} user_tmr;

typedef struct input_state_t {
    user_tmr tmr;
    uint32_t state;
    uint32_t prev_value;
} input_state;

uint32_t user_timer_get_tick(void);

uint32_t user_timer_setpoint (uint32_t delay);
uint32_t user_timer_get_setpoint (uint32_t timestamp, uint32_t time);
uint32_t user_timer_set_expired_setpoint (uint32_t time);
uint32_t user_timer_expired_setpoint (void);
uint32_t user_timer_start (user_tmr * user_tmr_ptr, uint32_t time);
uint32_t user_timer_start_expired (user_tmr * user_tmr_ptr);

uint32_t user_timer_expired (uint32_t set_point);
uint32_t user_timer_done (user_tmr * user_tmr_ptr);

uint32_t user_timer_interval (user_tmr * user_tmr_ptr, uint32_t interval);

uint32_t debounce (uint32_t pin, input_state * is, uint32_t time);
uint32_t delay_on (uint32_t pin, input_state * is, uint32_t time);
uint32_t delay_off (uint32_t pin, input_state * is, uint32_t time);


#ifdef	__cplusplus
}
#endif

#endif	/* USER_TIMER_H */

