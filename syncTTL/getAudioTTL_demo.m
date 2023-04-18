function audioTTLtime = getAudioTTL_demo(wavfilepath)
%{
    get TTL rise time from LSB of .wav file

    Dagher & Ishiyama (2023)
%}
    if ~nargin
        [wavFile,wavPath] = uigetfile('*.wav', 'Select wav file');
        wavfilepath = [wavPath, wavFile];
    end
    if ~wavfilepath
        return % user cancel
    end
    disp('Extracting Audio TTL...')
    [y, Fs] = audioread(wavfilepath, 'native');
    bitPos = 1;
    lsb = bitget(y, bitPos);
    upSamples = find(diff(lsb) == 1) + 1;
    audioTTLtime = upSamples / Fs;

end
