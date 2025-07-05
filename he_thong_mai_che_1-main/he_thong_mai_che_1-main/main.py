from flask import Flask, request, jsonify, render_template
import json
from datetime import datetime

app = Flask(__name__)

DATA_FILE = 'data.json'
COMMAND_FILE = 'command.json'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.json
    data['timestamp'] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    with open(DATA_FILE, 'a') as f:
        f.write(json.dumps(data) + '\n')

    print(">> Received from ESP32:", data)
    return jsonify({'status': 'success'}), 200

@app.route('/get-data', methods=['GET'])
def get_data():
    try:
        with open(DATA_FILE, 'r') as f:
            lines = f.readlines()
            data = [json.loads(line) for line in lines[-20:]]  # trả về 20 dòng gần nhất
        return jsonify(data)
    except Exception as e:
        return jsonify({'error': str(e)})

@app.route('/control', methods=['POST'])
def control_roof():
    command = request.json.get('command')
    with open(COMMAND_FILE, 'w') as f:
        json.dump({'command': command}, f)
    return jsonify({'status': 'command_sent'})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
