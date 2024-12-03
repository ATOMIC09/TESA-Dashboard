function labels = ConvertToLabels(falseArr, letterIfTrue, letterIfFalse, arrSize)
    % Initialize the result cell array with `letterIfTrue`
    labels = repmat(letterIfTrue, arrSize, 1);
    
    % Set positions in `falseArr` to `letterIfFalse`
    labels(falseArr) = letterIfFalse;
end
