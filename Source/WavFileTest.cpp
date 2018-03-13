/*
  ==============================================================================

    WavFileTest.cpp
    Created: 13 Mar 2018 11:57:35am
    Author:  zhao yan

  ==============================================================================
*/
#include "Glottis.h"
#include "AudioFileIf.h"
int main(int argc, char* argv[]) {
    int      sample_rate = 44100;
    int      num_channels = 1;
    int      block_size = 1024;
    int      num_block = 43;
    float  **output_data = 0;
    CAudioFileIf   *output_file = 0;
    Glottis* glottis_instance = 0;
    
    CAudioFileIf::create(output_file);
    CAudioFileIf::FileSpec_t output_file_spec;
    output_file_spec.eFormat = CAudioFileIf::FileFormat_t::kFileFormatWav;
    output_file_spec.fSampleRateInHz = sample_rate;
    output_file_spec.eBitStreamType = CAudioFileIf::BitStream_t::kFileBitStreamFloat32;
    output_file->openFile("./output.wav", CAudioFileIf::kFileWrite, &output_file_spec);
    //allocate memory for output buffer
    output_data = new float*[num_channels];
    for (int i = 0; i < num_channels; i++) {
        output_data[i] = new float[block_size];
    }
    
    glottis_instance = new Glottis(sample_rate, num_channels);
    for (int i = 0; i < num_block; i++) {
        glottis_instance->prosess(output_data, output_data, block_size);
        output_file->writeData(output_data, block_size);
    }
    
    CAudioFileIf::destroy(output_file);
    delete glottis_instance;
    for (int i = 0; i < num_channels; i++)
        delete[] output_data[i];
    delete[] output_data;
}






