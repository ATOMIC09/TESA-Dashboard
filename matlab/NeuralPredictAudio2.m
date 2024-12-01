function [predictResult, confidence] = NeuralPredictAudio2(feature) %#codegen
    persistent net classNames
    if isempty(net)
        net = coder.loadDeepLearningNetwork('model.mat', 'net');  % Load network once
    end
    if isempty(classNames)
        a = coder.load('model.mat', 'classNames');
        classNames = a.classNames;                         
    end
    score = predict(net, {feature});
    predictResult = scores2label(score, classNames, 2);
    confidence = max(score);
end
