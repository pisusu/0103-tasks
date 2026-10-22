import java.util.ArrayList;
import java.util.List;

public class HorseRace {

    // Список имён лошадей, которые уже финишировали
    static List<String> finishedHorses = new ArrayList<>();

    public static void main(String[] args) throws InterruptedException {

        // 10 Потоков лошадей и их старт
        List<Thread> horseThreads = new ArrayList<>();

        for (int horseNumber = 1; horseNumber <= 10; horseNumber++) {
            String horseName = "Лошадь " + horseNumber;
            Horse horse = new Horse(horseName);
            Thread horseThread = new Thread(horse);
            horseThreads.add(horseThread);
            horseThread.start();
        }

        // Ждём, пока финишируют 3 лошади
        while (finishedHorses.size() < 3) {
            Thread.sleep(20);
        }

        // Прерываем потоки методом interrupt
        for (Thread horseThread : horseThreads) {
            if (horseThread.isAlive()) {
                horseThread.interrupt();
            }
        }

        // Ждем пока потоки завершатся
        for (Thread horseThread : horseThreads) {
            horseThread.join();
        }

        // Призовые места
        System.out.println("\n=== ТРОЙКА ЛИДЕРОВ ===");
        for (int place = 1; place <= 3; place++) {
            System.out.println(place + " место: " + finishedHorses.get(place - 1));
        }
    }
}

class Horse implements Runnable {

    String horseName;

    Horse(String horseName) {
        this.horseName = horseName;
    }

    public void run() {
        try {
            // Всего 10 шагов до финиша
            for (int step = 1; step <= 10; step++) {

                System.out.println("Ждем лошадь " + horseName + " (шаг " + step + ")");

                // Стопаем лошадей чтобы скорость была разная
                int pause = 100 + (int) (Math.random() * 200);
                Thread.sleep(pause);
            }

            // Если лошадь доюежала - добавляется в список финишированых
            HorseRace.finishedHorses.add(horseName);
            System.out.println(">>> " + horseName + " ФИНИШИРОВАЛА");

        } catch (InterruptedException interruptedException) {
            // Если поток прервали - прекращается
            System.out.println(horseName + " остановлена (interrupt).");
        }
    }
}
