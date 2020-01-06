/* 
 * File:   system_tick.h
 * Author: Jacob
 *
 * Created on March 2, 2019, 5:18 PM
 */

#ifndef SYSTEM_TICK_H
#define	SYSTEM_TICK_H

#ifdef	__cplusplus
extern "C" {
#endif

    void sys_tick_init(void);
    uint32_t get_sys_tick(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_TICK_H */

