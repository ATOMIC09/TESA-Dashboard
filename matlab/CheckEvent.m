function [m, isCandidate] = CheckEvent(signal)
    %fil = designfilt('lowpassfir', ...
    %    'PassbandFrequency',10000,'StopbandFrequency',11000, ...
    %    'PassbandRipple',1,'StopbandAttenuation',60, ...
    %    'SampleRate',Fs,'DesignMethod','kaiserwin');
    Fs = 48000; % Example sample rate, replace with your actual Fs
    fp = 10000; % Passband frequency
    fs = 11000; % Stopband frequency
    Rp = 1;     % Passband ripple in dB
    Rs = 60;    % Stopband attenuation in dB
    
    % Normalized frequencies (0 to 1)
    Wp = fp / (Fs / 2); % Normalized passband frequency
    Ws = fs / (Fs / 2); % Normalized stopband frequency
    
    % Calculate the order of the filter
    delta_f = Ws - Wp;
    A = max(Rs, 21); % Minimum attenuation needed in dB
    
    if A > 50
        beta = 0.1102 * (A - 8.7);
    elseif A >= 21
        beta = 0.5842 * (A - 21)^0.4 + 0.07886 * (A - 21);
    else
        beta = 0;
    end
    
    N = ceil((A - 8) / (2.285 * delta_f * pi)); % Estimate filter order
    
    % Design the FIR filter using a Kaiser window
    b = fir1(N, Wp, kaiser(N + 1, beta));
    isCandidate = false;
    s = filter(b, 1, signal);
    m = mean(abs(s));
    if m > 0.33 && mean(abs(signal(1:100))) > 0.7
        isCandidate = true;
    end
end