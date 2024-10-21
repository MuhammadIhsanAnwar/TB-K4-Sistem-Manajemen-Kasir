window.onload = function() {
    if (performance.getEntriesByType("navigation")[0].type === "reload") {
        sessionStorage.clear();
    }

    if (!sessionStorage.getItem('justLoggedIn')) {
        document.getElementById("filter-form").submit(); 
        sessionStorage.setItem('justLoggedIn', 'true'); 
    }

    initCharts();
};

function initCharts() {
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
            type: 'line',
            borderWidth: 1,
            marker: {
                enabled: true
            }
        }, {
            name: 'Losses % Ampas Press',
            data: losis_ap,
            type: 'column',
            borderWidth: 1,
            color: 'rgba(0, 0, 255, 0.5)'
        }]
    });
    
    Highcharts.chart('bjChart', {
        chart: {
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
            type: 'line',
            borderWidth: 1,
            marker: {
                enabled: true
            }
        }, {
            name: 'Losses % Biji',
            data: losis_bj,
            type: 'column',
            borderWidth: 1,
            color: 'rgba(0, 0, 255, 0.5)'
        }]
    });
    
    Highcharts.chart('tkChart', {
        chart: {
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
            type: 'line',
            borderWidth: 1,
            marker: {
                enabled: true
            }
        }, {
            name: 'Losses % Tandan Kosong',
            data: losis_tk,
            type: 'column',
            borderWidth: 1,
            color: 'rgba(0, 0, 255, 0.5)'
        }]
    });
    
    Highcharts.chart('sdChart', {
        chart: {
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
            type: 'line',
            borderWidth: 1,
            marker: {
                enabled: true
            }
        }, {
            name: 'Losses % Solid Decanter',
            data: losis_sd,
            type: 'column',
            borderWidth: 1,
            color: 'rgba(0, 0, 255, 0.5)'
        }]
    });
    
    Highcharts.chart('daChart', {
        chart: {
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
            type: 'line',
            borderWidth: 1,
            marker: {
                enabled: true
            }
        }, {
            name: 'Losses % Drab Akhir',
            data: losis_da,
            type:  'column',
            borderWidth: 1,
            color: 'rgba(0, 0, 255, 0.5)'
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
}

setTimeout(() => {
    const alerts = document.querySelectorAll('.notification');
    alerts.forEach(alert => {
        alert.classList.add('fade-out');
        setTimeout(() => {
            alert.remove();
        }, 500);
    });
}, 3000);

document.getElementById('date-field').addEventListener('change', function() {
    document.getElementById('filter-form').submit();
});
