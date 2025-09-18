
% Step 1: User Input & handling invalid input
x = input('Enter distance from surface x [m ≥ 0]: ');
while x < 0
   x = input('Invalid. x must be ≥ 0. Enter distance x: ');
end




t = input('Enter time t [s > 0]: ');
while t <= 0
   t = input('Invalid. t must be > 0. Enter time t: ');
end




Ti = input('Enter initial temperature Ti [°C]: ');




q = input('Enter heat flux q [W/m^2 > 0]: ');
while q <= 0
   q = input('Invalid. q must be > 0. Enter heat flux q: ');
end




k = input('Enter thermal conductivity k [W/(m·K) > 0]: ');
while k <= 0
   k = input('Invalid. k must be > 0. Enter thermal conductivity k: ');
end




rho = input('Enter density rho [kg/m^3 > 0]: ');
while rho <= 0
   rho = input('Invalid. rho must be > 0. Enter density rho: ');
end




c = input('Enter specific heat capacity c [J/(kg·K) > 0]: ');
while c <= 0
c = input('Invalid. c must be > 0. Enter specific heat capacity c: ');
end




% Step 2: Calculate Temperature
alpha = k / (rho * c);  % Thermal diffusivity
term1 = (2 * q * sqrt(alpha * t / pi)) / k * exp(-x^2 / (4 * alpha * t));
term2 = (q * x / k) * (1 - erf(x / (2 * sqrt(alpha * t))));
T = Ti + term1 - term2;




% Step 3: show results
fprintf('\n--- Input Parameters ---\n');
fprintf('  x    = %.4f m\n', x);
fprintf('  t    = %.2f s\n', t);
fprintf('  Ti   = %.2f °C\n', Ti);
fprintf('  q    = %.2f W/m^2\n', q);
fprintf('  k    = %.2f W/(m·K)\n', k);
fprintf('  rho  = %.2f kg/m^3\n', rho);
fprintf('  c    = %.2f J/(kg·K)\n', c);




fprintf('\n--- Computed Temperature ---\n');
fprintf('At x = %.4f m and t = %.2f s, T = %.2f °C\n', x, t, T);




% Step 4: Plot Temperature graphs
x_vals = linspace(0, 0.1, 100);
t_vals = [200, 400, 600, 800];




figure; hold on;
for tt = t_vals
   term1_p = (2 * q * sqrt(alpha * tt / pi)) / k .* exp(-x_vals.^2 ./ (4 * alpha * tt));
   term2_p = (q .* x_vals / k) .* (1 - erf(x_vals ./ (2 * sqrt(alpha * tt))));
   T_p     = Ti + term1_p - term2_p;
   plot(x_vals, T_p, 'DisplayName', sprintf('t = %d s', tt));
end
xlabel('Distance x (m)');
ylabel('Temperature T (°C)');
title('Temperature Distribution vs. Distance at Different Times');
legend('Location', 'northeast');
grid on;
hold off;
