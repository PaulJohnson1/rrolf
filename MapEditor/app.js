const editor = document.getElementById("editor");
const grid = 20;
let isDragging = false;
let initialDragState = null;  // This will capture the state of the tile when dragging begins

// Create tiles
for (let y = 0; y < grid; y++) {
    for (let x = 0; x < grid; x++) {
        const tile = document.createElement('div');
        tile.classList.add('tile');
        tile.dataset.x = x;
        tile.dataset.y = y;
        tile.addEventListener('mousedown', startDrag);
        tile.addEventListener('mouseenter', dragToggle);
        editor.appendChild(tile);
    }
}

function startDrag(event) {
    event.preventDefault();  // Prevent the default drag behavior

    const tile = event.currentTarget;
    isDragging = true;
    initialDragState = tile.style.backgroundColor;

    // Immediately toggle the tile on mousedown
    toggleTile(event.currentTarget);
}


function toggleTile(tile) {
    if (selecting) return;

    if (initialDragState === 'black') {
        tile.style.backgroundColor = 'white';
    } else {
        tile.style.backgroundColor = 'black';
    }
}

function dragToggle(event) {
    if (isDragging) {
        toggleTile(event.currentTarget);
    }
}


document.getElementById('createZone').addEventListener('click', createZone);

let currentlyOpenedZone = null; // Used to keep track of which zone's details are being modified

function createZone() {
    const zone = document.createElement('li');
    zone.dataset.startX = 0;
    zone.dataset.startY = 0;
    zone.dataset.endX = 0;
    zone.dataset.endY = 0;
    zone.dataset.selected_color = "#ff0000";
    const zoneName = prompt("Enter zone name:", "New Zone");
    if (zoneName === null) return; // If user cancels the prompt
    
    zone.textContent = zoneName;
    zone.appendChild(createZoneDetailsButton());
    document.getElementById('zoneList').appendChild(zone);
}

function createZoneDetailsButton() {
    const btn = document.createElement('button');
    btn.textContent = "Details";
    btn.addEventListener('click', (event) => {
        const zone = event.target.parentElement;
        currentlyOpenedZone = zone;
        openZoneDetails(zone);
    });
    return btn;
}

function openZoneDetails(zone) {
    const panel = document.getElementById('zoneDetails');
    panel.classList.remove('hidden');
    document.getElementById('zoneName').value = zone.textContent.replace("Details", "").trim();

    document.getElementById('zoneName').addEventListener('input', updateZoneName);
    document.getElementById('difficulty').addEventListener('input', updateSliderValue);
    document.getElementById('spawnFrequency').addEventListener('input', updateSliderValue);
    document.getElementById('closePanel').addEventListener('click', closePanel);
}

function applyZoneColor(zone) {
    const color = zone.dataset.selected_color
    const startX = parseInt(zone.dataset.startX, 10);
    const startY = parseInt(zone.dataset.startY, 10);
    const endX = parseInt(zone.dataset.endX, 10);
    const endY = parseInt(zone.dataset.endY, 10);

    for (let y = startY; y <= endY; y++) {
        for (let x = startX; x <= endX; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            tile.style["background-color"] = color;
        }
    }
}

function resetZoneColor(zone)
{
    const startX = parseInt(zone.dataset.startX, 10);
    const startY = parseInt(zone.dataset.startY, 10);
    const endX = parseInt(zone.dataset.endX, 10);
    const endY = parseInt(zone.dataset.endY, 10);

    for (let y = startY; y <= endY; y++) {
        for (let x = startX; x <= endX; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            tile.style.backgroundColor = "";
        }
    }
}

function updateZoneName(event) {
    currentlyOpenedZone.firstChild.nodeValue = event.target.value;
}

function updateSliderValue(event) {
    const sliderId = event.target.id;
    const valueSpan = document.getElementById(sliderId + 'Value');
    valueSpan.textContent = event.target.value;
}

function closePanel() {
    const panel = document.getElementById('zoneDetails');
    panel.classList.add('hidden');

    document.querySelectorAll('.selected').forEach(tile => {
        tile.classList.remove('selected');
    });

    applyZoneColor(currentlyOpenedZone);

    // Remove the event listeners to prevent multiple bindings
    document.getElementById('zoneName').removeEventListener('input', updateZoneName);
    document.getElementById('difficulty').removeEventListener('input', updateSliderValue);
    document.getElementById('spawnFrequency').removeEventListener('input', updateSliderValue);
    document.getElementById('closePanel').removeEventListener('click', closePanel);
}


document.addEventListener('mouseup', () => {
    isDragging = false;
    initialDragState = null;
});

let selecting = false;
let startTile = null;
let endTile = null;

document.getElementById('selectDimensions').addEventListener('click', () => {
    selecting = true;
    document.getElementById('zoneDetails').classList.add('hidden');
    resetZoneColor(currentlyOpenedZone);
});

document.getElementById('zoneColorPicker').addEventListener('input', (event) => {
    currentlyOpenedZone.dataset.selected_color = event.target.value;  // Store color in the dataset for later use
    applyZoneColor(currentlyOpenedZone);
});

editor.addEventListener('mousedown', (event) => {
    if (event.target.classList.contains('tile')) {
        if (selecting) {
            startTile = event.target;
            isDragging = false;
        } else {
            isDragging = true;
            toggleTile(event.target);
        }
    }
});

editor.addEventListener('mousemove', (event) => {
    if (selecting && startTile) {
        endTile = event.target;
        
        // Highlight tiles between startTile and endTile
        const startX = parseInt(startTile.dataset.x, 10);
        const startY = parseInt(startTile.dataset.y, 10);
        const endX = parseInt(endTile.dataset.x, 10);
        const endY = parseInt(endTile.dataset.y, 10);

        // Clear previous selection
        document.querySelectorAll('.selected').forEach(tile => {
            tile.classList.remove('selected');
        });

        // Loop over the rectangle and select tiles
        for (let y = Math.min(startY, endY); y <= Math.max(startY, endY); y++) {
            for (let x = Math.min(startX, endX); x <= Math.max(startX, endX); x++) {
                const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
                tile.classList.add('selected');
            }
        }

        return;
    }

    if (isDragging && event.target.classList.contains('tile')) {
        toggleTile(event.target);
    }
});

editor.addEventListener('mouseup', (event) => {
    if (selecting && startTile) {
        // Highlight tiles between startTile and endTile
        const startX = parseInt(startTile.dataset.x, 10);
        const startY = parseInt(startTile.dataset.y, 10);
        const endX = parseInt(endTile.dataset.x, 10);
        const endY = parseInt(endTile.dataset.y, 10);

        const zoneX = Math.min(startX, endX);
        const zoneY = Math.min(startY, endY);
        const zoneW = Math.abs(endX - startX) + 1;
        const zoneH = Math.abs(endY - startY) + 1;

        currentlyOpenedZone.dataset.startX = zoneX;
        currentlyOpenedZone.dataset.startY = zoneY;
        currentlyOpenedZone.dataset.endX =  zoneX + zoneW - 1;
        currentlyOpenedZone.dataset.endY =  zoneY + zoneH - 1;

        document.getElementById('zoneX').textContent = zoneX;
        document.getElementById('zoneY').textContent = zoneY;
        document.getElementById('zoneW').textContent = zoneW;
        document.getElementById('zoneH').textContent = zoneH;

        selecting = false;
        startTile = null;
        endTile = null;
        // Show the panel again
        document.getElementById('zoneDetails').classList.remove('hidden');
    }
    isDragging = false;
    applyZoneColor(currentlyOpenedZone);
});

