document.addEventListener("DOMContentLoaded", function () {
  const fechaEntradaInput = document.querySelector('input[name="fecha_entrada"]');
  const fechaSalidaInput = document.querySelector('input[name="fecha_salida"]');

  const hoy = new Date();
  const tresMesesDespues = new Date();
  tresMesesDespues.setMonth(tresMesesDespues.getMonth() + 3);

  const formatoFecha = (fecha) => {
    const year = fecha.getFullYear();
    const month = String(fecha.getMonth() + 1).padStart(2, "0");
    const day = String(fecha.getDate()).padStart(2, "0");
    return `${year}-${month}-${day}`;
  };

  // Limitar fecha de entrada
  fechaEntradaInput.min = formatoFecha(hoy);
  fechaEntradaInput.max = formatoFecha(tresMesesDespues);

  // Al cambiar la fecha de entrada
  fechaEntradaInput.addEventListener("change", function () {
    const fechaSeleccionada = new Date(this.value);
    if (!isNaN(fechaSeleccionada)) {
      const fechaMaximaSalida = new Date(fechaSeleccionada);
      fechaMaximaSalida.setDate(fechaMaximaSalida.getDate() + 15);

      fechaSalidaInput.min = formatoFecha(fechaSeleccionada);
      fechaSalidaInput.max = formatoFecha(fechaMaximaSalida);
      fechaSalidaInput.value = "";
    }
  });
});
