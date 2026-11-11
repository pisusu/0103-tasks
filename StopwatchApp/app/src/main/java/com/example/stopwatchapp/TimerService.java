package com.example.stopwatchapp;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.SystemClock;

public class TimerService extends Service {
    private final IBinder binder = new LocalBinder();
    private long startTime = 0L;
    private long accumulatedTime = 0L;
    private boolean isRunning = false;

    public class LocalBinder extends Binder {
        TimerService getService() {
            return TimerService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public void startTimer() {
        if (!isRunning) {
            startTime = SystemClock.uptimeMillis() - accumulatedTime;
            isRunning = true;
        }
    }

    public void pauseTimer() {
        if (isRunning) {
            accumulatedTime = SystemClock.uptimeMillis() - startTime;
            isRunning = false;
        }
    }

    public void resetTimer() {
        accumulatedTime = 0L;
        startTime = SystemClock.uptimeMillis();
        isRunning = false;
    }

    public long getElapsedTime() {
        if (isRunning) {
            return SystemClock.uptimeMillis() - startTime;
        } else {
            return accumulatedTime;
        }
    }

    public boolean isRunning() {
        return isRunning;
    }
}
