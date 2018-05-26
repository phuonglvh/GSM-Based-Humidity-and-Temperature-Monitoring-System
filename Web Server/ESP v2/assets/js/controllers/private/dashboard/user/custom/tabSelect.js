
document.getElementById("progressbar").innerHTML = "Thiết bị của tôi";

var mydevice_tab = document.getElementById('mydevice-tab');
    monitor_tab = document.getElementById('monitor-tab');
    chart_tab = document.getElementById('chart-tab');
    warning_tab = document.getElementById('warning-tab');
    breadcrumb = document.getElementById('breadcrumb');

    /*Cards*/
    monitor_card = document.getElementById('monitor-card');
    chart_card = document.getElementById('chart-card');
    warning_card = document.getElementById('warning-card');

    /*Content*/
    monitor = document.getElementById('monitor');
    device = document.getElementById('mydevice');
    chart = document.getElementById('chart');
    warning = document.getElementById('warning');
    card = document.getElementById('card');

    /*Initial view*/
    card.style.display='block';
    device.style.display='block';
    
    monitor.style.display='none';
    chart.style.display='none';
    warning.style.display='none';
 

/*Breadcumb*/
breadcrumb.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Thiết bị của tôi";

    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item";
    chart_tab.className = "nav-item";
    warning_tab.className = "nav-item";

    card.style.display='block';
    device.style.display='block';
    monitor.style.display='none';
    chart.style.display='none';
    warning.style.display='none';
});

/*card*/
monitor_card.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "monitors";

    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item active";
    chart_tab.className = "nav-item ";
    warning_tab.className = "nav-item";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='block';
    chart.style.display='none';
    warning.style.display='none';
});

chart_card.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Trạng thái cảm biến";

    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item";
    chart_tab.className = "nav-item active";
    warning_tab.className = "nav-item";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='none';
    chart.style.display='block';
    warning.style.display='none';

});

warning_card.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Cảnh báo";

    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item";
    chart_tab.className = "nav-item";
    warning_tab.className = "nav-item active";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='none';
    chart.style.display='none';
    warning.style.display='block';
});


mydevice_tab.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Thiết bị của tôi";
    this.className = "nav-item active";
    monitor_tab.className = "nav-item";
    chart_tab.className = "nav-item";
    warning_tab.className = "nav-item";

    card.style.display='block';
    device.style.display='block';
    monitor.style.display='none';
    chart.style.display='none';
    warning.style.display='none';
});

monitor_tab.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Giám sát nhiệt độ - độ ẩm";

    this.className = "nav-item active";
    mydevice_tab.className = "nav-item";
    chart_tab.className = "nav-item";
    warning_tab.className = "nav-item";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='block';
    chart.style.display='none';
    warning.style.display='none';

}); 

chart_tab.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Trạng thái cảm biến";

    this.className = "nav-item active";
    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item";
    warning_tab.className = "nav-item";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='none';
    chart.style.display='block';
    warning.style.display='none';

}); 


warning_tab.addEventListener('click', function (event) {
    document.getElementById("progressbar").innerHTML = "Cảnh báo";

    this.className = "nav-item active";
    mydevice_tab.className = "nav-item";
    monitor_tab.className = "nav-item";
    chart_tab.className = "nav-item";

    card.style.display='none';
    device.style.display='none';
    monitor.style.display='none';
    chart.style.display='none';
    warning.style.display='block';
}); 

