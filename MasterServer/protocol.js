class BinaryWriter
{
    constructor() {
        const buf = new ArrayBuffer(8);
        this.conv_u8 = new Uint8Array(buf);
        this.conv_f32 = new Float32Array(buf);
        this.conv_f64 = new Float64Array(buf);
        this.data = new Uint8Array(256 * 1024); //files can't be more than 256kb and binary is more memory efficient so this is a good cap
        this.at = 1;
        this.data[0] = 1; //success byte
    }
    WriteUint8(u8) {
        this.data[this.at++] = u8;
    }
    WriteVarUint(vu) {
        while (vu > 127)
        {
            this.WriteUint8((vu << 1) | 1);
            vu >>= 7;
        }
        this.WriteUint8(vu << 1);
    }
    WriteStringNT(str) {
        const buf = new TextEncoder().encode(str);
        this.data.set(buf, this.at);
        this.at += buf.length;
        this.WriteUint8(0);
    }
    WriteFloat32(f32) {
        this.conv_f32[0] = f32;
        this.data.set(this.conv_u8.subarray(0,4), this.at);
        this.at += 4;
    }
    WriteFloat64(f64) {
        this.conv_f64[0] = f64;
        this.data.set(this.conv_u8, this.at);
        this.at += 8;
    }
}

class BinaryReader
{

}

module.exports = { BinaryReader, BinaryWriter };
