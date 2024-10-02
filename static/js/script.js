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
const pieData = JSON.parse(document.getElementById('pieData').textContent); // Data untuk Pie Chart
const areaData = JSON.parse(document.getElementById('areaData').textContent); // Data untuk Area Chart

// Membuat grafik bar menggunakan Highcharts
Highcharts.chart('barChart', {
    chart: {
        type: 'column' // Jenis grafik kolom
    },
    title: {
        text: 'Produksi per Provinsi' // Judul grafik
    },
    xAxis: {
        categories: ['Aceh', 'Sumatera Utara'] // Ganti dengan kategori dari provinsi Anda
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Produksi' // Judul sumbu y
        }
    },
    series: [{
        name: 'Produksi', // Nama seri
        data: barData, // Data dari elemen JSON
        color: 'rgba(54, 162, 235, 0.2)', // Warna latar belakang
        borderColor: 'rgba(54, 162, 235, 1)', // Warna border
        borderWidth: 1 // Lebar border
    }]
});

// Membuat grafik garis menggunakan Highcharts
Highcharts.chart('lineChart', {
    title: {
        text: 'Luas Panen per Provinsi' // Judul grafik
    },
    xAxis: {
        categories: ['Aceh', 'Sumatera Utara'] // Ganti dengan kategori dari provinsi Anda
    },
    yAxis: {
        title: {
            text: 'Luas Panen' // Judul sumbu y
        }
    },
    series: [{
        name: 'Luas Panen', // Nama seri
        data: lineData, // Data dari elemen JSON
        type: 'line', // Jenis grafik garis
        fill: false,
        color: 'rgba(255, 99, 132, 1)', // Warna garis
        lineWidth: 2 // Lebar garis
    }]
});

// Membuat grafik pie menggunakan Highcharts
Highcharts.chart('pieChart', {
    chart: {
        type: 'pie' // Jenis grafik pie
    },
    title: {
        text: 'Distribusi Produksi per Provinsi' // Judul grafik
    },
    series: [{
        name: 'Produksi',
        data: pieData, // Data dari elemen JSON
        colorByPoint: true // Warna berdasarkan poin
    }]
});

// Membuat grafik area menggunakan Highcharts
Highcharts.chart('areaChart', {
    chart: {
        type: 'area' // Jenis grafik area
    },
    title: {
        text: 'Curah Hujan per Provinsi' // Judul grafik
    },
    xAxis: {
        categories: ['Aceh', 'Sumatera Utara'] // Ganti dengan kategori dari provinsi Anda
    },
    yAxis: {
        title: {
            text: 'Curah Hujan' // Judul sumbu y
        }
    },
    series: [{
        name: 'Curah Hujan', // Nama seri
        data: areaData, // Data dari elemen JSON
        fillColor: {
            linearGradient: { x1: 0, y1: 0, x2: 0, y2: 1 }, // Gradien warna
            stops: [
                [0, 'rgba(255, 99, 132, 1)'], // Warna atas
                [1, 'rgba(255, 99, 132, 0.1)'] // Warna bawah
            ]
        },
        marker: {
            enabled: false // Menonaktifkan marker
        }
    }]
});
