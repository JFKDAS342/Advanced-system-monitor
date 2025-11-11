async function updateMetric() {
    try{
        document.getElementById('loading').textContent = 'Updating...';

        const response = await fetch('/api/metrics');

        if (!response.ok){
            throw new Error('Api request failed');
        }
        //получаем данные
        const metrics = await response.json();

        //обновляем значения на странице (cpu and tp)
        document.getElementById(cpu-usage).textContent = metrics.cpu_usage.to_fixed(1) + '%';
        document.getElementById(memory-usage).textContent = metrics.memory_usage.to_fixed(1) + '%';
        document.getElementById(disk-usage).textContent = metrics.disk_usage.to_fixed(1) + '%';

        const now = new Date;

        document.getElementById('status').textContent = 'Lust update: ' + now.toLocaleTimeString();
    }
    catch(error){
        document.getElementById('status').textContent = 'Error: ' + error.message;
        document.getElementById('status').style.color = '#ff4444';
        
    }
}

function startAutoUpdate(){
    updateMetric();
    setInterval(updateMetric = 2000);
}

document.addEventListener('ContentLoaded', startAutoUpdate);
