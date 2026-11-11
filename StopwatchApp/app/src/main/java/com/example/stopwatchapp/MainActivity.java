package com.example.stopwatchapp;

import androidx.appcompat.app.AppCompatActivity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.provider.Settings;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView tvTimer;
    private Button btnStartStop, btnReset;

    private FloatingWindowService timerService;
    private boolean isBound = false;
    private Handler handler = new Handler(Looper.getMainLooper());
    private static final int OVERLAY_CODE = 1234;

    // Подключение к сервису
    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            FloatingWindowService.LocalBinder binder = (FloatingWindowService.LocalBinder) service;
            timerService = binder.getService();
            isBound = true;
            updateUI();
            // Если таймер был запущен до того, как мы открыли приложение - запускаем обновление экрана
            if (timerService.isRunning()) {
                btnStartStop.setText("Стоп");
                btnReset.setEnabled(false);
                handler.post(updateThread);
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            isBound = false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvTimer = findViewById(R.id.tvTimer);
        btnStartStop = findViewById(R.id.btnStartStop);
        btnReset = findViewById(R.id.btnReset);

        // Привязываем Activity к Сервису
        Intent intent = new Intent(this, FloatingWindowService.class);
        bindService(intent, connection, Context.BIND_AUTO_CREATE);

        btnStartStop.setOnClickListener(v -> {
            if (isBound) {
                if (!timerService.isRunning()) {
                    timerService.startTimer();
                    btnStartStop.setText("Стоп");
                    btnReset.setEnabled(false);
                    handler.post(updateThread);
                } else {
                    timerService.pauseTimer();
                    btnStartStop.setText("Старт");
                    btnReset.setEnabled(true);
                    handler.removeCallbacks(updateThread);
                }
            }
        });

        btnReset.setOnClickListener(v -> {
            if (isBound) {
                timerService.resetTimer();
                tvTimer.setText("00:00:00");
                btnStartStop.setText("Старт");
                btnReset.setEnabled(false);
                handler.removeCallbacks(updateThread);
            }
        });
    }

    private final Runnable updateThread = new Runnable() {
        @Override
        public void run() {
            if (isBound) {
                updateUI();
                handler.postDelayed(this, 50);
            }
        }
    };

    private void updateUI() {
        if (isBound) {
            long timeMs = timerService.getElapsedTime();
            int seconds = (int) (timeMs / 1000);
            tvTimer.setText(String.format("%02d:%02d:%02d", seconds / 60, seconds % 60, (timeMs % 1000) / 10));
        }
    }

    // --- ОТПРАВЛЯЕМ СЕРВИС В ФОН (Плавающее окно) ---
    @Override
    protected void onStop() {
        super.onStop();
        // Если свернули приложение и таймер идет
        if (isBound && timerService.isRunning()) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(this)) {
                // Если нет разрешения - просим
                startActivityForResult(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName())), OVERLAY_CODE);
            } else {
                showOverlay();
            }
        }
    }

    private void showOverlay() {
        Intent intent = new Intent(this, FloatingWindowService.class);
        intent.putExtra("showOverlay", true); // Говорим сервису показать окошко
        startService(intent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == OVERLAY_CODE && Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (Settings.canDrawOverlays(this)) showOverlay();
        }
    }

    // Когда возвращаемся в приложение - прячем окошко
    @Override
    protected void onResume() {
        super.onResume();
        if (isBound) {
            timerService.hideFloatingWindow();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        handler.removeCallbacks(updateThread);
        if (isBound) {
            unbindService(connection);
            isBound = false;
        }
    }
}

