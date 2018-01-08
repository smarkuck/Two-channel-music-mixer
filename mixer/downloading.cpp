#include <downloading.h>
#include <soundprocessing.h>
#include <lame/lame.h>

Downloading::Downloading(SoundProcessing* soundprocessing, QObject *parent) : QObject(parent)
{
 this->soundProc = soundprocessing;
}
void Downloading::download(QString filename){

    qDebug() << " Downloading started " ;
    QString wavfilename;
    if(filename.endsWith(".mp3")){
        wavfilename = filename + ".wav";
    }
    else{
        wavfilename = filename;
    }
    QFile* file= new QFile(wavfilename);

    file->open(QIODevice::Append);
    //wpisanie headera formatu WAVE do pliku
    writeWavHeader(file);
    //wpisanie danych z dzwiekiem
    file->write(soundProc->output1);
    file->close();

    if(filename.endsWith(".mp3")){
        writeMp3Header(wavfilename);
        file->remove(wavfilename);
    }
    emit downloadReady();
    qDebug() << "ready";

}


void Downloading::writeWavHeader( QFile * file )
{
    QDataStream out(file);
    out.setByteOrder(QDataStream::LittleEndian);

    // RIFF chunk
    out.writeRawData("RIFF", 4);
    out << quint32(0); // Placeholder for the RIFF chunk size (filled by close())
    out.writeRawData("WAVE", 4);

    // Format description chunk
    out.writeRawData("fmt ", 4);
    out << quint32(16); // "fmt " chunk size (always 16 for PCM)
    out << quint16(1); // data format (1 => PCM)
    out << quint16(soundProc->format.channelCount());
    out << quint32(soundProc->format.sampleRate());
    out << quint32(soundProc->format.sampleRate() * soundProc->format.channelCount()
                   * soundProc->format.sampleSize() / 8 ); // bytes per second
    out << quint16(soundProc->format.channelCount() * soundProc->format.sampleSize() / 8); // Block align
    out << quint16(soundProc->format.sampleSize()); // Significant Bits Per Sample

    // Data chunk
    out.writeRawData("data", 4);
    out << quint32(0); // Placeholder for the data chunk size (filled by close())

}

void Downloading::writeMp3Header( QString wavFilename )
{
    const char* pcmName = wavFilename.toLocal8Bit().constData();
    QString mp3file = wavFilename.left(wavFilename.count()-4);
    const char* mp3name = mp3file.toLocal8Bit().constData();

    FILE *pcm = fopen(pcmName, "rb");
    FILE *mp3 = fopen(mp3name, "wb");
    size_t nread;
    int ret, nwrite;

    // 1. Get lame version (OPTIONAL)
    printf("Using LAME v%s\n", get_lame_version());

    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;

    short pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];

    // 2. Initializing
    lame_t lame = lame_init();

    // 3. Do some settings (OPTIONAL)
    lame_set_in_samplerate(lame, 48000);
    lame_set_VBR(lame, vbr_default);
    lame_set_VBR_quality(lame, 2);

    // 4. Initialize parameters
    ret = lame_init_params(lame);
    if (ret < 0) {
        printf("Error occurred during parameters initializing. Code = %d\n",
                ret);
        return ;
    }

    do {
        // Read PCM_SIZE of array
        nread = fread(pcm_buffer, 2 * sizeof(short), PCM_SIZE, pcm);
        if (nread != 0) {
            // 5. Encode
            int nsamples = nread;
            short buffer_l[nsamples];
            short buffer_r[nsamples];

           // printf("nread = %d\n", nread);
            //printf("pcm_buffer.length = %d\n", sizeof(pcm_buffer)/sizeof(short));

            int j = 0;
            int i = 0;
            for (i = 0; i < nsamples; i++) {
                buffer_l[i] = pcm_buffer[j++];
                buffer_r[i] = pcm_buffer[j++];

            }

            nwrite = lame_encode_buffer(lame, buffer_l, buffer_r, nread,
                    mp3_buffer, MP3_SIZE);
        } else {
            // 6. Flush and give some final frames
            nwrite = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        }

        if (nwrite < 0) {
            printf("Error occurred during encoding. Code = %d\n", nwrite);
            return ;
        }

        fwrite(mp3_buffer, nwrite, 1, mp3);
    } while (nread != 0);

    // 7. Write INFO tag (OPTIONAL)
    // lame_mp3_tags_fid(lame, mp3);

    // 8. Free internal data structures
    lame_close(lame);

    fclose(mp3);
    fclose(pcm);
}
