from flask import Flask, request, render_template, jsonify
from datetime import datetime

app = Flask(__name__)

latest_grid = [[0]*8 for _ in range(8)]

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/update', methods=['POST'])
def update():
    global latest_grid
    data = request.get_json()
    flat = data.get("tempGrid", [0]*64)
    latest_grid = [flat[i:i+8] for i in range(0, 64, 8)]
    return "OK", 200

@app.route('/data')
def data():
    return jsonify(latest_grid)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
