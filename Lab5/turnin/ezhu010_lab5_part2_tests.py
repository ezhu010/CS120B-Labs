tests = [
    {
        "description": "PINA: 0x01 => PORTC: 8",
        "steps": [{"inputs": [("PINA", 0x01)], "iterations": 1}],
        "expected": [("PORTC", 8)],
    },
    {
        "description": "PINA: 0x01 PINA: 0x03 => PORTC: 0",
        "steps": [
            {"inputs": [("PINA", 0x01)], "iterations": 3},
            {"inputs": [("PINA", 0x03)], "iterations": 3},
        ],
        "expected": [("PORTC", 0x00)],
    },
    {
        "description": "PINA: 0x01 PINA: 0x03 PINA: 0x01 => PORTC:0x01",
        "steps": [
            {"inputs": [("PINA", 0x01)], "iterations": 3},
            {"inputs": [("PINA", 0x03)], "iterations": 3},
            {"inputs": [("PINA", 0x01)], "iterations": 3},
        ],
        "expected": [("PORTC", 0x01)],
    },
    {
        "description": "PINA: 0x01 PINA: 0x03 PINA: 0x01 PINA: 0x00 PINA: 0x02 => PORTC:0x00",
        "steps": [
            {"inputs": [("PINA", 0x01)], "iterations": 3},
            {"inputs": [("PINA", 0x03)], "iterations": 3},
            {"inputs": [("PINA", 0x01)], "iterations": 3},
            {"inputs": [("PINA", 0x00)], "iterations": 1},
            {"inputs": [("PINA", 0x02)], "iterations": 1},
        ],
        "expected": [("PORTC", 0x00)],
    },
]

