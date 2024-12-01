function [predictResult, confidence] = NeuralPredictAudio(x) %#codegen
    persistent net classNames
    if isempty(net)
        net = coder.loadDeepLearningNetwork('model.mat', 'net');  % Load network once
    end
    if isempty(classNames)
        a = coder.load('model.mat', 'classNames');
        classNames = a.classNames;                         
    end
    feats = ExtractFeatures(x, 48000);
    score = predict(net, {feats});
    predictResult = scores2label(score, classNames, 2);
    confidence = max(score);
end
