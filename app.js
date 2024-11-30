document.addEventListener("DOMContentLoaded", () => {
  const sopas = [
    { id: 1, nombre: "Sopa de abodora", precio: 150, img: "sopa de abodora.jpg" },
    { id: 2, nombre: "Sopa de Champiñones", precio: 185, img: "crema-de-champinones.jpg" },
    { id: 3, nombre: "Sopa de Pollo", precio: 200, img: "sopa-de-pollo.jpg" },
  ];

  const platos = [
    { id: 1, nombre: "Ensalada", precio: 385, img: "Ensalada_César.jpg" },
    { id: 2, nombre: "Pizza Margherita", precio: 320, img: "Margherita" },
    { id: 3, nombre: "Espaguetis Bolognesa", precio: 270, img: "spaghetty.jpeg" },
  ];

  const bebidas = [
    { id: 1, nombre: "zumo de naranja", precio: 50, img: "zumo.jpg" },
    { id: 2, nombre: "zumo de uva", precio: 30, img: "zumo de uva.jpg" },
    { id: 3, nombre: "zumo multifruta", precio: 120, img: "multifruta.jpg" },
  ];

  const gridSopas = document.querySelector(".menu .grid.sopas");
  const gridPlatos = document.querySelector(".menu .grid.platos");
  const gridBebidas = document.querySelector(".menu .grid.bebidas");

  const resumenSopa = document.getElementById("pedido-sopa");
  const resumenPrincipal = document.getElementById("pedido-principal");
  const resumenBebida = document.getElementById("pedido-bebida");
  const total = document.getElementById("pedido-total");

  const calcularTotal = () => {
    const precios = [resumenSopa, resumenPrincipal, resumenBebida].map((input) =>
      parseInt(input.dataset.precio || 0)
    );
    total.textContent = `${precios.reduce((a, b) => a + b, 0)} ₽`;
  };

  const renderItems = (items, grid, tipo) => {
    items.forEach((item) => {
      const card = document.createElement("div");
      card.className = "card";
      card.innerHTML = `<img src="${item.img}" alt="${item.nombre}">
      <h3>${item.nombre}</h3>
      <p>${item.precio} ₽</p><button>Seleccionar</button>`;
      card.querySelector("button").addEventListener("click", () => {
        const resumen = tipo === "sopa" ? resumenSopa : tipo === "plato" ? resumenPrincipal : resumenBebida;
        resumen.value = item.nombre;
        resumen.dataset.precio = item.precio;
        calcularTotal();
      }); 
      grid.appendChild(card);
    });
  };

  renderItems(sopas, gridSopas, "sopa");
  renderItems(platos, gridPlatos, "plato");
  renderItems(bebidas, gridBebidas, "bebida");

  // Activar el input de hora cuando se seleccione la opción "Seleccionar hora"
  document.getElementById("tiempo-pedido").addEventListener("change", (event) => {
    const horaSeleccionada = document.getElementById("hora-seleccionada");
    if (event.target.value === "hora_seleccionada") {
      horaSeleccionada.style.display = "block";
    } else {
      horaSeleccionada.style.display = "none";
    }
  });

  // Validar el formulario antes de confirmar el pedido
  const form = document.getElementById("pedido-form");
  form.addEventListener("submit", (e) => {
    const nombre = document.getElementById("nombre").value;
    const email = document.getElementById("email").value;
    const telefono = document.getElementById("telefono").value;
    const direccion = document.getElementById("direccion").value;
    const tiempoPedido = document.getElementById("tiempo-pedido").value;
    const hora = document.getElementById("hora").value;
    const minutos = document.getElementById("minutos").value;
    const segundos = document.getElementById("segundos").value;
    const errorMessage = document.getElementById("error-message");

    if (!nombre || !email || !telefono || !direccion || !tiempoPedido || 
        (tiempoPedido === "hora_seleccionada" && (!hora || !minutos || !segundos))) {
      e.preventDefault();
      errorMessage.style.display = "block"; // Mostrar mensaje de error
    }
  });
});
