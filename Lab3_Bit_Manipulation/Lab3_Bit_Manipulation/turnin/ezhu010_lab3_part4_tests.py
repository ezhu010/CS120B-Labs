




tests = [ {'description': 'PINA: 0x63 => PORTB: 0x06 PORTC: 0x30',
    'steps': [ {'inputs': [('PINA',0x63)], 'iterations': 5 } ],
    'expected': [('PORTB',0x06),('PORTC',0x30)]
        },


	{'description': 'PINA: 0xAB => PORTB: 0x0A PORTC: 0xB0',
    'steps': [ {'inputs': [('PINA',0xAB)], 'iterations': 5 } ],
    'expected': [('PORTB',0x0A),('PORTC',0xB0)]
        },


	{'description': 'PINA: 0x71 => PORTB: 0x07 PORTC: 0x10',
    'steps': [ {'inputs': [('PINA',0x71)], 'iterations': 5 } ],
    'expected': [('PORTB',0x07),('PORTC',0x10)]
        },

  ]
