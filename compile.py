import sys
import struct


def parse_operand(operand: str):
    if ':' in operand:
        a, b = operand.split(':', 1)
        from_registry = a.startswith('r')

        value = int(a[1:] if from_registry else a)

        return b, value, from_registry
    elif operand.startswith('r'):
        return 'u32', int(operand[1:]), True
    elif len(operand) > 0:
        return 'id', operand, False
    else:
        return None, None, None


def pack_operator(operator):
    operators = {
        'in':  0x00,
        'mov': 0x01,
        'add': 0x02,
        'out': 0x03,
        'jmp': 0x04,
        'nop': 0xFF
    }
    return struct.pack('B', operators[operator])


def parse_kind(kind):
    kinds = {
        'i8': ('b', 0x01),
        'i16': ('h', 0x02),
        'i32': ('i', 0x03),
        'i64': ('q', 0x04),
        'u8': ('B', 0x05),
        'u16': ('H', 0x06),
        'u32': ('I', 0x07),
        'u64': ('Q', 0x08),
        'f32': ('f', 0x09),
        'f64': ('d', 0x0A)
    }

    return kinds[kind]


def pack_operand(operand):
    kind, value, from_registry = operand
    flags = 0x00

    if kind.startswith('*'):
        flags |= (1 << 4)  # set flag for pointer
        kind = kind[1:]

    tag, code = parse_kind(kind)

    if from_registry:
        flags |= (1 << 7)  # set flag for register
        return struct.pack('<BB', flags | code, value)
    else:
        return struct.pack('<B' + tag, flags | code, value)


def main(input_file, output_file):
    output = open(output_file, 'wb')
    output.write(struct.pack('<HHI', 0, 0, 0))

    labels = dict()

    for line in open(input_file, 'rb'):
        line = line.decode('utf8').strip()

        # check if we have a label
        if line.endswith(':'):
            label = line[:-1]
            labels[label] = output.tell() - 8
            print(labels)
        else:
            try:
                operator, operands_str = line.split(' ', 1)
            except ValueError:
                operator = line
                operands_str = ''

            operands = tuple(map(str.strip, operands_str.split(',')))
            operands_parsed = tuple(map(parse_operand, operands))

            print(operator, operands_parsed)

            output.write(pack_operator(operator))
            for op in operands_parsed:
                if op[0] == 'id':
                    op = ('u32', labels[op[1]], False)

                output.write(pack_operand(op))


if __name__ == '__main__':
    if len(sys.argv) > 2:
        main(sys.argv[1], sys.argv[2])
