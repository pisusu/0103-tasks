package com.example.stopwatchapp;

import android.app.Service;
import android.content.Intent;
import android.graphics.PixelFormat;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.TextView;

public class FloatingWindowService extends Service {

    // --- 1. ЛОГИКА ДЛЯ ОЦЕНКИ "ОТЛИЧНО" (Хранение времени) ---
    private final IBinder binder = new LocalBinder();
    private long startTime = 0L;
    private long accumulatedTime = 0L;
    private boolean isRunning = false;

    public class LocalBinder extends Binder {
        FloatingWindowService getService() {
            return FloatingWindowService.this;
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


    // --- 2. ЛОГИКА ДЛЯ ПЛАВАЮЩЕГО ОКНА (Красота) ---
    private WindowManager windowManager;
    private TextView tvFloatingTimer;
    private Handler handler = new Handler(Looper.getMainLooper());

    // Этот поток обновляет текст в плавающем окне
    private final Runnable updateOverlayThread = new Runnable() {
        @Override
        public void run() {
            if (tvFloatingTimer != null) {
                long timeMs = getElapsedTime();
                int seconds = (int) (timeMs / 1000);
                tvFloatingTimer.setText(String.format("%02d:%02d:%02d", seconds / 60, seconds % 60, (timeMs % 1000) / 10));
                handler.postDelayed(this, 50);
            }
        }
    };

    @Override
    public void onCreate() {
        super.onCreate();
        windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // Этот метод вызывается из MainActivity, когда мы сворачиваем приложение
        // и хотим показать плавающее окно.
        if (intent != null && intent.hasExtra("showOverlay")) {
            showFloatingWindow();
        }
        return START_STICKY;
    }

    private void showFloatingWindow() {
        if (tvFloatingTimer != null) return; // Если окно уже есть, не создаем второе

        tvFloatingTimer = new TextView(this);
        tvFloatingTimer.setTextSize(24);
        tvFloatingTimer.setPadding(30, 30, 30, 30);
        tvFloatingTimer.setBackgroundColor(0xAA000000);
        tvFloatingTimer.setTextColor(0xFFFFFFFF);

        int type = android.os.Build.VERSION.SDK_INT >= 26
                ? WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY
                : WindowManager.LayoutParams.TYPE_PHONE;

        WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT,
                type, WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE, PixelFormat.TRANSLUCENT);

        params.gravity = Gravity.TOP | Gravity.END;
        params.x = 50;
        params.y = 100;

        windowManager.addView(tvFloatingTimer, params);
        handler.post(updateOverlayThread); // Запускаем обновление текста в окне
    }

    public void hideFloatingWindow() {
        if (tvFloatingTimer != null) {
            handler.removeCallbacks(updateOverlayThread);
            windowManager.removeView(tvFloatingTimer);
            tvFloatingTimer = null;
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        hideFloatingWindow();
    }
}
