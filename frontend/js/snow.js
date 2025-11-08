// Ждем когда страница полностью загрузится
document.addEventListener('DOMContentLoaded', function() {
    startSnowAnimation();
});

function startSnowAnimation() {
    //  Находим элемент canvas в HTML
    const canvas = document.getElementById('snowCanvas');
    
    // Получаем инструменты для рисования
    const ctx = canvas.getContext('2d');
    
    // Настраиваем размер canvas под весь экран
    function setupCanvasSize() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    }
    
    setupCanvasSize(); // Вызываем сразу
    window.addEventListener('resize', setupCanvasSize); // И при изменении размера окна
    
    
    let snowflakes = [];
    
    // Создаем 100 снежинок со случайными параметрами
    function createSnowflakes() {
        for (let i = 0; i < 100; i++) {
            snowflakes.push({
                x: Math.random() * canvas.width,      // Случайная позиция X
                y: Math.random() * canvas.height,     // Случайная позиция Y
                size: Math.random() * 3 + 1,          // Размер от 1 до 4
                speed: Math.random() * 2 + 1,         // Скорость от 1 до 3
                wind: (Math.random() - 0.5) * 0.5,    // Ветер от -0.25 до +0.25
                opacity: Math.random() * 0.5 + 0.3    // Прозрачность от 0.3 до 0.8
            });
        }
    }
    
    createSnowflakes();
    
    //  Функция рисования одной снежинки
    function drawSnowflake(flake) {
        ctx.beginPath(); // Начинаем новый путь
        ctx.arc(flake.x, flake.y, flake.size, 0, Math.PI * 2); // Рисуем круг
        ctx.fillStyle = `rgba(255, 255, 255, ${flake.opacity})`; // Белый с прозрачностью
        ctx.fill(); // Заливаем цветом
    }
    
    
    function updateSnowflake(flake) {
        // Двигаем снежинку вниз
        flake.y += flake.speed;
        
        // Добавляем движение в сторону
        flake.x += flake.wind;
        
        // Если снежинка упала за нижний край - возвращаем наверх
        if (flake.y > canvas.height) {
            flake.y = 0;
            flake.x = Math.random() * canvas.width;
        }
        
        // Если улетела за бок - появляется с другой стороны
        if (flake.x > canvas.width) flake.x = 0;
        if (flake.x < 0) flake.x = canvas.width;
    }
    
    // Главная функция анимации
    function animate() {
        // Очищаем canvas от предыдущего кадра
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        
        // Для каждой снежинки обновляем позицию и рисуем
        snowflakes.forEach(flake => {
            updateSnowflake(flake);
            drawSnowflake(flake);
        });
        
        // Запускаем следующий кадр анимации
        requestAnimationFrame(animate);
    }
    
    // 9. Запускаем анимацию!
    animate();
}