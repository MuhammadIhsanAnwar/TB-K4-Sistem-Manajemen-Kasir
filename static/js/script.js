// Menghapus notifikasi setelah 3 detik
setTimeout(() => {
    const alerts = document.querySelectorAll('.notification');
    alerts.forEach(alert => {
        alert.classList.add('fade-out');
        setTimeout(() => {
            alert.remove();
        }, 500); 
    });
}, 3000);

// Ambil data dari elemen JSON
const barData = JSON.parse(document.getElementById('barData').textContent);
const lineData = JSON.parse(document.getElementById('lineData').textContent);
const pieData = JSON.parse(document.getElementById('pieData').textContent);  
const areaData = JSON.parse(document.getElementById('areaData').textContent);  
const provinsi = JSON.parse(document.getElementById('provinsi').textContent);
 
Highcharts.chart('barChart', {
    chart: {
        type: 'column'  
    },
    title: {
        text: 'Produksi per Provinsi'  
    },
    xAxis: {
        categories: provinsi  
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Produksi'  
        }
    },
    series: [{
        name: 'Produksi', 
        data: barData, 
        color: 'rgba(54, 162, 235, 0.2)', 
        borderColor: 'rgba(54, 162, 235, 1)', 
        borderWidth: 1  
    }]
}); 

Highcharts.chart('lineChart', {
    title: {
        text: 'Luas Panen per Provinsi' 
    },
    xAxis: {
        categories: provinsi 
    },
    yAxis: {
        title: {
            text: 'Luas Panen'    
        }
    },
    series: [{
        name: 'Luas Panen', 
        data: lineData,  
        type: 'line',  
        fill: false,
        color: 'rgba(255, 99, 132, 1)',  
        lineWidth: 2  
    }]
});
 
Highcharts.chart('pieChart', {
    chart: {
        type: 'pie'  
    },
    title: {
        text: 'Distribusi Produksi per Provinsi'  
    },
    series: [{
        name: 'Produksi',
        data: pieData,  
        colorByPoint: true  
    }]
});

Highcharts.chart('areaChart', {
    chart: {
        type: 'area'  
    },
    title: {
        text: 'Curah Hujan per Provinsi'  
    },
    xAxis: {
        categories: provinsi  
    },
    yAxis: {
        title: {
            text: 'Curah Hujan'  
        }
    },
    series: [{
        name: 'Curah Hujan',  
        data: areaData, 
        fillColor: {
            linearGradient: { x1: 0, y1: 0, x2: 0, y2: 1 }, 
            stops: [
                [0, 'rgba(255, 99, 132, 1)'],  
                [1, 'rgba(255, 99, 132, 0.1)']  
            ]
        },
        marker: {
            enabled: false  
        }
    }]
});
