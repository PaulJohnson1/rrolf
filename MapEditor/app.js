// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

const editor = document.getElementById("editor");
const GRID_SIZE = 40;
let isDragging = false;
let initialDragState = null;  // This will capture the state of the tile when dragging begins
let zone_count = 0;

// Create tiles
for (let y = 0; y < GRID_SIZE; y++) {
    for (let x = 0; x < GRID_SIZE; x++) {
        const tile = document.createElement('div');
        tile.classList.add('tile');
        tile.dataset.x = x;
        tile.dataset.y = y;
        tile.dataset.d = 0;
        tile.addEventListener('mousedown', startDrag);
        tile.addEventListener('mouseenter', dragToggle);
        editor.appendChild(tile);
    }
}

function startDrag(event) {
    event.preventDefault();  // Prevent the default drag behavior
    
    const tile = event.currentTarget;
    if (event.buttons === 2)
    {
        built = true;

        document.querySelectorAll('.spawn').forEach(tile => {
            tile.classList.remove('spawn');
            tile.style.backgroundColor = "";
        });
        tile.style.backgroundColor = "red";
        tile.classList.add("spawn");
        return;
    }
    isDragging = true;
    initialDragState = tile.style.backgroundColor;

    // Immediately toggle the tile on mousedown
    toggleTile(event.currentTarget);
}

function refreshDistances() {
    const walls = getWalls();
    const spawnElement = document.querySelector(".spawn");
    if (!spawnElement)
        return;
    const spawn = [+spawnElement.dataset.x, +spawnElement.dataset.y];

    const ds = floodFill(walls, spawn);
    for (let x = 0; x < ds.length; x++)
        for (let y = 0; y < ds.length; y++)
        {
            let d = ds[x][y];
            if (d == Infinity)
                d = "i";
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            tile.dataset.d = d;
            tile.textContent = d == "i" ? "" : d;
        }
}

function onDoneBuilding()
{
    console.log("refreshing");
    refreshDistances();
}

let currentRefreshTimeout;

function toggleTile(tile) {
    if (selecting) return;
    if (tile.classList.contains("spawn")) return;

    let built = false;

    if (initialDragState === 'black') {
        tile.style.backgroundColor = '';
        built = true;
    } else {
        tile.style.backgroundColor = 'black';
        built = true;
    }

    if (built)
    {
        clearTimeout(currentRefreshTimeout);
        currentRefreshTimeout = setTimeout(onDoneBuilding, 1000);
    }
}

function getWalls()
{
    const walls = [];
    for (let y = 0; y < GRID_SIZE; y++) {
        const row = [];
        for (let x = 0; x < GRID_SIZE; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            row.push(tile.style.backgroundColor === 'black' ? 1 : 0);
        }
        walls.push(row);
    }

    return walls;
}

function dragToggle(event) {
    if (isDragging) {
        toggleTile(event.currentTarget);
    } else {
        document.querySelectorAll('.pathed').forEach(tile => {
            tile.classList.remove('pathed');
        });
        const walls = getWalls();

        const spawnElement = document.querySelector(".spawn");
        if (!spawnElement)
            return;
        const spawn = [+spawnElement.dataset.x, +spawnElement.dataset.y];
        const target = [+event.currentTarget.dataset.x, +event.currentTarget.dataset.y];
        const path = bfs(walls, spawn, target);
        for (let i = 0; i < path.length; i++)
        {
            const [x, y] = path[i];
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            tile.classList.add("pathed");
        }
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
    zone.dataset.index = zone_count++;
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
        zoneColorPicker.value = currentlyOpenedZone.dataset.selected_color;
    });
    return btn;
}

function createZoneElement(startX, startY, endX, endY, color, label) {
    // Create the main zone container
    const zoneElement = document.createElement('li');
    zoneElement.dataset.startX = startX;
    zoneElement.dataset.startY = startY;
    zoneElement.dataset.endX = endX;
    zoneElement.dataset.endY = endY;
    zoneElement.dataset.selected_color = color;
    zoneElement.textContent = label;

    zoneElement.appendChild(createZoneDetailsButton());
    document.getElementById('zoneList').appendChild(zoneElement);

    applyZoneColor(zoneElement);
    applyZoneClassToTiles(zoneElement);

    return zoneElement;
}

function openZoneDetails(zone) {
    const panel = document.getElementById('zoneDetails');
    panel.classList.remove('hidden');
    document.getElementById('zoneName').value = zone.textContent.replace("Details", "").trim();

    document.getElementById('zoneName').addEventListener('input', updateZoneName);
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
            tile.style.backgroundColor = color;
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

function applyZoneClassToTiles(zone) {
    const startX = parseInt(zone.dataset.startX, 10);
    const startY = parseInt(zone.dataset.startY, 10);
    const endX = parseInt(zone.dataset.endX, 10);
    const endY = parseInt(zone.dataset.endY, 10);

    for (let y = startY; y <= endY; y++) {
        for (let x = startX; x <= endX; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            tile.dataset.zone_index = zone.dataset.index
            tile.classList.add('zone');
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
    endTile = event.target;
    console.log(endTile.dataset.x, endTile.dataset.y);
    if (selecting && startTile) {
        
        
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
    applyZoneClassToTiles(currentlyOpenedZone);
});

document.getElementById('importData').addEventListener('click', () => {
    document.getElementById('importInput').click();
});

document.getElementById('importInput').addEventListener('change', (event) => {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const importData = JSON.parse(e.target.result);
            
            // Restore Zones (as before)
            const zones = importData.zones;
            zones.forEach(zone => {
                const newZone = createZoneElement(zone.startX, zone.startY, zone.endX, zone.endY, zone.color, zone.label);
            });

            // Restore Walls based on color
            const walls = importData.walls;
            for (let y = 0; y < GRID_SIZE; y++) {
                for (let x = 0; x < GRID_SIZE; x++) {
                    const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
                    if (walls[y][x] === 1) {
                        tile.style.backgroundColor = 'black';
                    } else {
                        tile.style.backgroundColor = ''; // reset to default
                    }
                }
            }
        };
        reader.readAsText(file);
    }
});

document.getElementById('exportData').addEventListener('click', () => {
    const zones = [...zoneList.children].map(zone => ({
        startX: zone.dataset.startX,
        startY: zone.dataset.startY,
        endX: zone.dataset.endX,
        endY: zone.dataset.endY,
        color: zone.dataset.selected_color,
        label: zone.firstChild.nodeValue,
    }));

    const walls = [];
    for (let y = 0; y < GRID_SIZE; y++) {
        const row = [];
        for (let x = 0; x < GRID_SIZE; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            row.push(tile.style.backgroundColor === 'black' ? 1 : 0);
        }
        walls.push(row);
    }

    const exportData = {
        zones,
        walls
    };

    const dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(exportData));
    const downloadAnchorNode = document.createElement('a');
    downloadAnchorNode.setAttribute("href", dataStr);
    downloadAnchorNode.setAttribute("download", "map_data.json");
    document.body.appendChild(downloadAnchorNode);
    downloadAnchorNode.click();
    downloadAnchorNode.remove();
});

function generateMaze() {
    const MAZE_SIZE = GRID_SIZE;
    const i = (x, y) => x + y * MAZE_SIZE;

    const visited_map = new Uint8Array(MAZE_SIZE * MAZE_SIZE);
    const maze = new Uint8Array(MAZE_SIZE * MAZE_SIZE).fill(1);

    const stack = [];

    const append = (x, y) => {
        stack.push([x, y]);
        visited_map[i(x, y)] = 1;
        maze[i(x, y)] = 0;
    };

    append(0, 0);

    while (stack.length)
    {
        const [x, y] = stack.at(-1);

        let neighbors = [];

        if (y + 2 < MAZE_SIZE && !visited_map[i(x, y + 2)])
            neighbors.push(0);
        if (y - 2 > 0 &&         !visited_map[i(x, y - 2)])
            neighbors.push(1);
        if (x + 2 < MAZE_SIZE && !visited_map[i(x + 2, y)])
            neighbors.push(2);
        if (x - 2 > 0 &&         !visited_map[i(x - 2, y)])
            neighbors.push(3);

        if (neighbors.length === 0)
        {
            stack.pop();
            continue;
        }

        const d = neighbors[Math.floor(Math.random() * neighbors.length)];
        switch (d)
        {
            case 0:
                append(x, y + 2);
                maze[i(x, y + 1)] = 0;
                break;
            case 1:
                append(x, y - 2);
                maze[i(x, y - 1)] = 0;
                break;
            case 2:
                append(x + 2, y);
                maze[i(x + 1, y)] = 0;
                break;
            case 3:
                append(x - 2, y);
                maze[i(x - 1, y)] = 0;
                break;
        }
    }

    return maze;
}

function bfs(maze, start, end) {
    const MAZE_SIZE = maze.length;
    const visited = Array(MAZE_SIZE).fill(false).map(() => Array(MAZE_SIZE).fill(false));
    const prev = Array(MAZE_SIZE).fill(null).map(() => Array(MAZE_SIZE).fill(null));
    const queue = [start];

    function isValid(x, y) {
        return x >= 0 && y >= 0 && x < MAZE_SIZE && y < MAZE_SIZE;
    }

    while (queue.length) {
        const [x, y] = queue.shift();

        if (x === end[0] && y === end[1]) {
            const path = [];
            let curr = end;
            while (curr && !(curr[0] === start[0] && curr[1] === start[1])) {
                path.push(curr);
                curr = prev[curr[1]][curr[0]];
            }
            path.push(start);  // Don't forget to add the start point.
            return path.reverse();
        }

        // Direction: Up
        const newX1 = x;
        const newY1 = y - 1;
        if (isValid(newX1, newY1) && !visited[newY1][newX1] && maze[newY1][newX1] !== 1) {
            visited[newY1][newX1] = true;
            prev[newY1][newX1] = [x, y];
            queue.push([newX1, newY1]);
        }

        // Direction: Right
        const newX2 = x + 1;
        const newY2 = y;
        if (isValid(newX2, newY2) && !visited[newY2][newX2] && maze[newY2][newX2] !== 1) {
            visited[newY2][newX2] = true;
            prev[newY2][newX2] = [x, y];
            queue.push([newX2, newY2]);
        }

        // Direction: Down
        const newX3 = x;
        const newY3 = y + 1;
        if (isValid(newX3, newY3) && !visited[newY3][newX3] && maze[newY3][newX3] !== 1) {
            visited[newY3][newX3] = true;
            prev[newY3][newX3] = [x, y];
            queue.push([newX3, newY3]);
        }

        // Direction: Left
        const newX4 = x - 1;
        const newY4 = y;
        if (isValid(newX4, newY4) && !visited[newY4][newX4] && maze[newY4][newX4] !== 1) {
            visited[newY4][newX4] = true;
            prev[newY4][newX4] = [x, y];
            queue.push([newX4, newY4]);
        }
    }

    return [];
}

function floodFill(matrix, spawn) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    const distances = Array(rows).fill(Infinity).map(() => Array(cols).fill(Infinity));

    // Check if the position is within the matrix boundaries and not an obstacle.
    function isValid(x, y) {
        return x >= 0 && y >= 0 && x < cols && y < rows && matrix[y][x] !== 1;
    }

    const queue = [{x: spawn[0], y: spawn[1], distance: 0}];

    while(queue.length) {
        const current = queue.shift();

        // Skip if this position has been visited with a shorter or equal distance.
        if (distances[current.x][current.y] <= current.distance)
            continue;

        distances[current.x][current.y] = current.distance;

        const directions = [[0, -1], [1, 0], [0, 1], [-1, 0]];
        for(let dir of directions) {
            const newX = current.x + dir[0];
            const newY = current.y + dir[1];

            if(isValid(newX, newY) && distances[newX][newY] > current.distance + 1) {
                queue.push({x: newX, y: newY, distance: current.distance + 1});
            }
        }
    }

    return distances;
}

createRandom.addEventListener("mousedown", () => {
    const walls = generateMaze();
    const i = (x, y) => x + y * GRID_SIZE;

    for (let y = 0; y < GRID_SIZE; y++) {
        for (let x = 0; x < GRID_SIZE; x++) {
            const tile = document.querySelector(`.tile[data-x="${x}"][data-y="${y}"]`);
            if (walls[i(x, y)] === 1) {
                tile.style.backgroundColor = 'black';
            } else {
                tile.style.backgroundColor = ''; // reset to default
            }
        }
    }
})
