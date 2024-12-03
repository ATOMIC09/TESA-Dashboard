function features = ExtractFeatures(x, Fs) %#codegen
    avg = mean(x);
    power_stdv = std(abs(x));
    rms_val = rms(x);
    
    windowLength = floor(length(x)/500);
    window = hamming(windowLength, "periodic");
    overlap = floor(windowLength/2); % 50% overlap

    coeffs = mfcc(x', Fs, 'Window', window, 'OverlapLength', overlap);
    coeffs = (coeffs - mean(coeffs, 1)) ./ std(coeffs, [], 1);

    % Pack the extracted feature vector to a new row of the feature matrix X
    %coeffs = reshape(coeffs, 1, []);
    
    %c = modwt(x', 'db2', 15);

    features = [coeffs];
end