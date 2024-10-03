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
const pks_name = JSON.parse(document.getElementById('pks_name').textContent);
const norma_ap = JSON.parse(document.getElementById('norma_ap').textContent);
const losis_ap = JSON.parse(document.getElementById('losis_ap').textContent);
const norma_bj = JSON.parse(document.getElementById('norma_bj').textContent);
const losis_bj = JSON.parse(document.getElementById('losis_bj').textContent);
const norma_tk = JSON.parse(document.getElementById('norma_tk').textContent);
const losis_tk = JSON.parse(document.getElementById('losis_tk').textContent);
const norma_da = JSON.parse(document.getElementById('norma_da').textContent);
const losis_da = JSON.parse(document.getElementById('losis_da').textContent);
const norma_sd = JSON.parse(document.getElementById('norma_sd').textContent);
const losis_sd = JSON.parse(document.getElementById('losis_sd').textContent);
const norma_pks = JSON.parse(document.getElementById('norma_pks').textContent);
const losis_pks = JSON.parse(document.getElementById('losis_pks').textContent);

Highcharts.chart('apChart', {
    chart: {
        type: 'column'
    },
    title: {
        text: 'Losses Ampas Press'
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Persentase (%)'
        }
    },
    series: [{
        name: 'Norma Ampas Press',
        data: norma_ap,
        borderWidth: 1
    }, {
        name: 'Losses % Ampas Press',
        data: losis_ap,
        borderWidth: 1
    }]
});

Highcharts.chart('bjChart', {
    chart: {
        type: 'column'
    },
    title: {
        text: 'Losses Biji'
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Persentase (%)'
        }
    },
    series: [{
        name: 'Norma Biji',
        data: norma_bj,
        borderWidth: 1
    }, {
        name: 'Losses % Biji',
        data: losis_bj,
        borderWidth: 1
    }]
});

Highcharts.chart('tkChart', {
    chart: {
        type: 'column'
    },
    title: {
        text: 'Losses Tandan Kosong'
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Persentase (%)'
        }
    },
    series: [{
        name: 'Norma Tandan Kosong',
        data: norma_tk,
        borderWidth: 1
    }, {
        name: 'Losses % Tandan Kosong',
        data: losis_tk,
        borderWidth: 1
    }]
});

Highcharts.chart('sdChart', {
    chart: {
        type: 'column'
    },
    title: {
        text: 'Losses Solid Decanter'
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        min: 0,
        title: {
            text: 'Persentase (%)'
        }
    },
    series: [{
        name: 'Norma Solid Decanter',
        data: norma_sd,
        borderWidth: 1
    }, {
        name: 'Losses % Solid Decanter',
        data: losis_sd,
        borderWidth: 1
    }]
});

Highcharts.chart('daChart', {
    chart: {
        type: 'area'
    },
    title: {
        text: 'Losses Drab Akhir'
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        title: {
            text: 'Persentase (%)'
        }
    },
    series: [{
        name: 'Norma Drab Akhir',
        data: norma_da,
        marker: {
            enabled: false
        }
    }, {
        name: 'Losses % Drab Akhir',
        data: losis_da,
        fillColor: {
            linearGradient: { x1: 0, y1: 0, x2: 0, y2: 1 },
            stops: [
                [0, 'rgba(255, 99, 132, 1)'],
                [1, 'rgba(255, 99, 132, 0.3)']
            ]
        },
        marker: {
            enabled: false
        }
    }]
});

Highcharts.chart('pksChart', {
    chart: {
        type: 'line'
    },
    title: {
        text: 'Losses PKS',
    },
    xAxis: {
        categories: pks_name
    },
    yAxis: {
        title: {
            text: 'Persentase (%)'
        }
    },
    tooltip: {
        shared: true,
        crosshairs: true
    },
    series: [{
        name: 'Norma PKS',
        data: norma_pks
    }, {
        name: 'Losses % PKS',
        data: losis_pks
    }],
    responsive: {
        rules: [{
            condition: {
                maxWidth: 500
            },
            chartOptions: {
                legend: {
                    align: 'center',
                    verticalAlign: 'bottom',
                    layout: 'horizontal'
                }
            }
        }]
    }
});
