// Function to fetch and display webcam feed
function displayWebcamFeed() {
    // Endpoint URL for fetching webcam feed
    const webcamFeedUrl = 'http://192.168.86.23:8080/'; // Replace with your actual RPI cam server address and port

    // Select the div where you want to display the webcam feed
    const webcamFeedDiv = document.getElementById('camera-feed');

    // Create a new HTML <img> element to display the webcam feed
    const webcamImage = document.createElement('img');

    // Set attributes for the image element
    webcamImage.src = webcamFeedUrl; // Set the source of the image to the webcam feed URL
    webcamImage.alt = 'Webcam Feed'; // Provide an alt attribute for accessibility

    // Append the image element to the webcam feed div
    webcamFeedDiv.appendChild(webcamImage);
}