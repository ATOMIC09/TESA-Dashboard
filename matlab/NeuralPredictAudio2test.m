feature = ExtractFeatures(XF2(46, :), 48000);
disp(feature);
[p, c] = NeuralPredictAudio2(feature);
disp(p);
disp(c);