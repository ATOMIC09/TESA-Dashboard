for i = 1:5
    figure;
    mfcc(XF1(i, :)', Fs, 'Window', window, 'OverlapLength', overlap)
end