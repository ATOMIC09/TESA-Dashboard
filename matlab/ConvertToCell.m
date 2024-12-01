function cell = ConvertToCell(arr)
    cell = mat2cell(arr, ones(size(arr, 1), 1), size(arr, 2), size(arr, 3));
    cell = cellfun(@(x) squeeze(x), cell, 'UniformOutput', false);
end