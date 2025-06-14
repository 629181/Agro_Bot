// Function to fetch data from ESP32
async function fetchSensorData() {
    try {
        // Replace with your ESP32's local IP and endpoint
        const response = await fetch('http://192.168.0.103/sensor-data');
        const data = await response.json();

        // Update the UI with new values
        document.getElementById('temperature').textContent = data.temperature.toFixed(1);
        document.getElementById('humidity').textContent = data.humidity.toFixed(1);
        document.getElementById('gas').textContent = data.gas.toFixed(0);
        document.getElementById('soil').textContent = data.soil.toFixed(1);

        // Update last updated time
        const now = new Date();
        document.getElementById('lastUpdated').textContent = now.toLocaleTimeString();

        // Check conditions for growing
        const temp = parseFloat(data.temperature);
        const hum = parseFloat(data.humidity);
        const soilMoist = parseFloat(data.soil);
        
        if (temp >= 25 && temp <= 35 && 
            hum >= 70 && hum <= 90 && 
            soilMoist >= 60 && soilMoist <= 80) {
            document.getElementById('recommendation').textContent = 'Rice can be grown';
        }
        
        else if (temp < 15 && temp > 25 &&
                hum < 50 && hum > 60 &&
                soilMoist < 40 && soilMoist > 60) {
            document.getElementById('recommendation').textContent = 'Wheat can be grown';
        }

        else if (temp < 20 && temp > 30 &&
            hum < 50 && hum > 70 &&
            soilMoist < 40 && soilMoist > 60) {
        document.getElementById('recommendation').textContent = 'Maize can be grown';
        }

        else if (temp < 15 && temp > 20 &&
            hum < 60 && hum > 80 &&
            soilMoist < 60 && soilMoist > 70) {
        document.getElementById('recommendation').textContent = 'Potato can be grown';
        }

        else if (temp < 20 && temp > 30 &&
             hum < 50 && hum > 70 &&
            soilMoist < 50 && soilMoist > 70) {
        document.getElementById('recommendation').textContent = 'Tomato can be grown';
        }
        else if (temp < 26 && temp > 35 &&
            hum < 60 && hum > 80 &&
            soilMoist < 60 || soilMoist > 80) {
        document.getElementById('recommendation').textContent = 'Sugarcane can be grown';
        }
        else if (temp < 25 && temp > 35 &&
            hum < 40 && hum > 60 &&
            soilMoist < 30 && soilMoist > 50) {
        document.getElementById('recommendation').textContent = 'Cotton can be grown';
        }
        else if (temp < 20 && temp > 30 &&
            hum < 60 && hum > 70 &&
            soilMoist < 30 && soilMoist > 50) {
        document.getElementById('recommendation').textContent = 'Soybean can be grown';
        }
        else if (temp < 20 && temp > 30 &&
            hum < 40 && hum > 60 &&
            soilMoist < 30 && soilMoist > 50) {
        document.getElementById('recommendation').textContent = 'Chili can be grown';
        }
        else if (temp < 20 && temp > 25 &&
            hum < 55 && hum > 65 &&
            soilMoist < 35 && soilMoist > 60) {
        document.getElementById('recommendation').textContent = 'Onion can be grown';
        }
        else {
            document.getElementById('recommendation').textContent = 'Nothing to grow';
        }

    } catch (error) {
        console.error('Error fetching sensor data:', error);
    }
    
}

// Fetch data immediately and then every 5 seconds
fetchSensorData();
setInterval(fetchSensorData, 2000);